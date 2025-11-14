#include <iostream>
#include <algorithm>
#include <vector>

int main(){
	std::vector<int> a = {5,2,9,1,3};
	std::sort(a.begin(),a.end());

	for(int x : a) std::cout<<x<<" ";

	std::string s = "dbca";
	std::sort(s.begin(),s.end());
	std::cout<<s;

	std::vector<std::pair<int,int>> v = {{3,4},{1,2},{3,1}};
	std::sort(v.begin(),v.end());
	for(auto &p : v){
		std::cout<<"("<<p.first<<","<<p.second<<")";
	}
	std::cout<<std::endl;

	return 0;
}
