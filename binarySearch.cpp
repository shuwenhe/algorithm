#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int> &num,int target){
	int middle;                          // 1,3,5,7,9
	int left = 0,right = num.size() - 1; // 0,1,2,3,4
	while(left<right){
		middle = left+(right-left)/2;
		if(num[middle]<target){
			left = middle+1;
		}else{
			right = middle-1;
		}
	}
	return middle+1;
}

int main(){
	vector<int> num = {1,3,5,7,9,11,13,15,17,18,20,21};
	int target = 21; //0,1,2,3,4,5, 6, 7, 8, 9, 10,11  
	int result = binarySearch(num,target);
	cout<<"result = "<<result<<endl;
	return 0;
}

