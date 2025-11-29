#include <iostream>

using namespace std;

int binarySearch(vector<int> &num,int target){
	int middle;
	int left,right;
	while(left<=right){
		middle = left+(right-left)/2;
		if(num.left<num.middle){
			left = middle+1;
		}else{
			right = middle-1;
		}
		return middle;
	}
	return -1;
}

int main(){
	vector<int> num = {1,3,5,7,9,11,13,15};
	int target;
	int result = binarySearch(num,target);
	return 0;
}

