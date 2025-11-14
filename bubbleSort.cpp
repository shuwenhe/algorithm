#include <iostream>
#include <vector>
using namespace std;
vector<int> arr = {3,1,5,9,7};

void bubbleSort(vector<int>& arr){
	int n = arr.size();
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(arr[j] > arr[j + 1]){
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

void printArr(){
	int n = arr.size();
	for(int i = 0; i < n; i++){
		cout<<arr[i]<<',';
	}
	cout<<endl;
}

int main(){
	printArr();
	bubbleSort(arr);
	printArr();
}
