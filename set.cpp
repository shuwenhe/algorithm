#include <iostream>
#include <set>

int main(){
	std::set<int> s;

	s.insert(5);
	s.insert(2);
	s.insert(9);
	s.insert(1);
	s.insert(3);
	s.insert(2); // 重复元素，不会插入

	for(int x : s) std::cout<<x<<" ";
}
