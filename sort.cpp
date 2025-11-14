#include <iostream>
#include <algorithm>
#include <vector>

int main(){
	std::vector<int> a = {5,2,9,1,3};
	std::sort(a.begin(),a.end());

	for(int x : a) std::cout<<x<<" ";
	return 0;
}
