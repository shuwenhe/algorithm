/*
写一个装饰器模式的示例
*/
package main

import "fmt"

// 定义Coffee Interface
type Coffee interface {
	Price() float64
	Description() string
}

// 基础Coffee实现
type SimpleCoffee struct{}

func (s *SimpleCoffee) Price() float64 {
	return 5.0
}

func (s *SimpleCoffee) Description() string {
	return "simple coffee"
}

// 装饰器基类，实现Coffee Interface
type CoffeeDecorator struct {
	coffee Coffee
}

func (c *CoffeeDecorator) Price() float64 {
	return c.coffee.Price()
}

func (c *CoffeeDecorator) Description() string {
	return c.coffee.Description()
}

// Milk 装饰器
type Milk struct {
	CoffeeDecorator
}

func NewMilk(coffee Coffee) *Milk {
	return &Milk{CoffeeDecorator{coffee: coffee}}
}

func (m *Milk) Price() float64 {
	return m.coffee.Price() + 1.5
}

func (m *Milk) Description() string {
	return m.coffee.Description() + ", milk"
}

// Sugar装饰器
type Sugar struct {
	CoffeeDecorator
}

func NewSugar(coffee Coffee) *Sugar {
	return &Sugar{CoffeeDecorator{coffee: coffee}}
}

func (s *Sugar) Price() float64 {
	return s.coffee.Price() + 0.5
}

func (s *Sugar) Description() string {
	return s.coffee.Description() + ", Add sugar"
}

// WhippedCream 装饰器
type WhippedCream struct {
	CoffeeDecorator
}

func NewWhippedCream(coffee Coffee) *WhippedCream {
	return &WhippedCream{CoffeeDecorator{coffee: coffee}}
}

func (w *WhippedCream) Price() float64 {
	return w.coffee.Price() + 2.0
}

func (w *WhippedCream) Description() string {
	return w.coffee.Description() + ", Add milk"
}

func main() {
	// Simple coffle
	var coffee Coffee = &SimpleCoffee{}
	fmt.Printf("%s: ￥%.2f\n", coffee.Description(), coffee.Price())
        // Add ilk
	coffee = NewMilk(coffee)
	fmt.Printf("%s: ￥%.2f\n", coffee.Description(), coffee.Price())
	// Add sugar
	coffee = NewSugar(coffee)
	fmt.Printf("%s: ￥%.2f\n", coffee.Description(), coffee.Price())
	// Add milk
	coffee = NewWhippedCream(coffee)
	fmt.Printf("%s: ￥%.2f\n", coffee.Description(), coffee.Price())
	// All in Coffee
	superCoffee := NewWhippedCream(NewSugar(NewMilk(&SimpleCoffee{})))
	fmt.Printf("\n%s: ￥%.2f\n", superCoffee.Description(), superCoffee.Price())
}


