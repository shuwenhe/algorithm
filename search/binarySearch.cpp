#include<bits/stdc++.h>

bool binarySearch(const std::vector<int>& vec, int target) {
	auto it = std::lower_bound(vec.begin(), vec.end(), target);// 检查是否找到目标且目标位于向量中
	return (it != vec.end() && *it == target);
}

int main() {
	std::vector<int> myVector = {1, 2, 4, 5, 7, 8, 10};
	int target = 5;
	bool found = binarySearch(myVector, target);
	std::cout << "Element " << target << " is " << (found ? "found" : "not found") << " in the vector." << std::endl;
	return 0;
}
