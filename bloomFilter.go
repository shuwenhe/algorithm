package main

import (
	"hash/fnv"
	"fmt"
	"sync"
	"time"
)

const ( // 常量定义
	WindowSize    = 5 * time.Minute // 5分钟窗口
	CleanInterval = time.Minute     // 清理间隔
	MaxQPS        = 100000          // 目标QPS
	MaxMemory     = 256 * 1024 * 1024 // 256MB最大内存
	BloomFilterSize = 16 * 1024 * 1024 // 16MB每窗口 布隆过滤器参数
	HashFunctions   = 5                // 哈希函数数量
)

type BloomFilter struct { // 布隆过滤器结构
	bits  []uint64
	m     uint64 // 位数组大小
	k     uint8  // 哈希函数数量
	mutex sync.RWMutex
}

func NewBloomFilter(size uint64, hashCount uint8) *BloomFilter {// 新建布隆过滤器
	return &BloomFilter{
		bits: make([]uint64, (size+63)/64),
		m:    size,
		k:    hashCount,
	}
}

func (bf *BloomFilter) hash(data []byte, i int) uint64 {// 哈希函数
	switch i {
	case 0:
		h := fnv.New64a()
		h.Write(data)
		return h.Sum64()
	case 1:
		h := fnv.New64()
		h.Write(data)
		return h.Sum64()
	default:
		h1 := fnv.New64a() // 基于前两个哈希生成更多哈希
		h1.Write(data)
		v1 := h1.Sum64()
		h2 := fnv.New64()
		h2.Write(data)
		v2 := h2.Sum64()
		return v1 + uint64(i)*v2
	}
}

// 添加元素
func (bf *BloomFilter) Add(data []byte) {
	bf.mutex.Lock()
	defer bf.mutex.Unlock()
	for i := uint8(0); i < bf.k; i++ {
		hash := bf.hash(data, int(i))
		index := hash % bf.m
		bf.bits[index/64] |= 1 << (index % 64)
	}
}

// 检查元素是否存在
func (bf *BloomFilter) Contains(data []byte) bool {
	bf.mutex.RLock()
	defer bf.mutex.RUnlock()
	for i := uint8(0); i < bf.k; i++ {
		hash := bf.hash(data, int(i))
		index := hash % bf.m
		if (bf.bits[index/64] & (1 << (index % 64))) == 0 {
			return false
		}
	}
	return true
}

// 滑动窗口管理器
type WindowManager struct {
	windows    []*BloomFilter
	windowSize time.Duration
	numWindows int
	currentIdx int
	mutex      sync.RWMutex // 改为读写锁，支持RLock/RUnlock
}

// 新建窗口管理器
func NewWindowManager(totalWindow time.Duration, cleanInterval time.Duration) *WindowManager {
	numWindows := int(totalWindow / cleanInterval)
	windows := make([]*BloomFilter, numWindows)
	for i := 0; i < numWindows; i++ {
		windows[i] = NewBloomFilter(uint64(BloomFilterSize)*8, HashFunctions)
	}
	return &WindowManager{
		windows:    windows,
		windowSize: cleanInterval,
		numWindows: numWindows,
		currentIdx: 0,
	}
}

// 清理过期窗口
func (wm *WindowManager) Cleanup() {
	wm.mutex.Lock()
	defer wm.mutex.Unlock()
	wm.currentIdx = (wm.currentIdx + 1) % wm.numWindows// 移动到下一个窗口并重置
	wm.windows[wm.currentIdx] = NewBloomFilter(uint64(BloomFilterSize)*8, HashFunctions)
}

// 添加记录
func (wm *WindowManager) Add(data []byte) {
	wm.mutex.Lock()
	defer wm.mutex.Unlock()
	wm.windows[wm.currentIdx].Add(data)
}

// 检查记录是否存在于任何窗口
func (wm *WindowManager) Exists(data []byte) bool {
	wm.mutex.RLock()
	defer wm.mutex.RUnlock()
	for _, window := range wm.windows {
		if window.Contains(data) {
			return true
		}
	}
	return false
}

// 风控网关
type RiskGateway struct {
	windowManager *WindowManager
	threshold     int // 允许的最大加购次数
	counter       map[string]int // 精确计数，用于少量高频操作
	counterMutex  sync.RWMutex
}

// 新建风控网关
func NewRiskGateway(threshold int) *RiskGateway {
	wm := NewWindowManager(WindowSize, CleanInterval)
	// 启动定时清理
	go func() {
		ticker := time.NewTicker(CleanInterval)
		defer ticker.Stop()
		for range ticker.C {
			wm.Cleanup()
		}
	}()
	return &RiskGateway{
		windowManager: wm,
		threshold:     threshold,
		counter:       make(map[string]int),
	}
}

// 生成唯一键：用户ID+商品ID
func (rg *RiskGateway) generateKey(userId, productId string) string {
	return userId + ":" + productId
}

// 检查加购请求是否合法
func (rg *RiskGateway) CheckAddToCart(userId, productId string) bool {
	key := rg.generateKey(userId, productId)
	keyBytes := []byte(key)
	// 先检查布隆过滤器
	if rg.windowManager.Exists(keyBytes) {
		// 存在则检查精确计数
		rg.counterMutex.RLock()
		count := rg.counter[key]
		rg.counterMutex.RUnlock()
		if count >= rg.threshold {
			return false // 超过阈值，拒绝请求
		}
		// 未超过阈值，增加计数
		rg.counterMutex.Lock()
		rg.counter[key]++
		rg.counterMutex.Unlock()
		return true
	}
	// 不存在则添加到布隆过滤器和计数器
	rg.windowManager.Add(keyBytes)
	rg.counterMutex.Lock()
	rg.counter[key] = 1
	rg.counterMutex.Unlock()
	return true
}

func main() {
	// 初始化风控网关，设置阈值为5次
	gateway := NewRiskGateway(5)
	userId := "user123"
	productId := "product456"
	// 正常请求
	for i := 0; i < 5; i++ {
		if gateway.CheckAddToCart(userId, productId) {
			fmt.Printf("第%d次加购成功\n", i+1)
		} else {
			fmt.Printf("第%d次加购被拒绝\n", i+1)
		}
	}
	// 第6次应该被拒绝
	if gateway.CheckAddToCart(userId, productId) {
		fmt.Println("第6次加购成功")
	} else {
		fmt.Println("第6次加购被拒绝")
	}
}

