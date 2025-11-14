#include <iostream>
#include <vector>

using namespace std;

void quickSort(){

}

int main(){
	vector<int> arr = {64,34,25,12,22,11,90};
	int n = arr.size();
	quickSort(arr,0,n - 1);
	cout<<n<<endl;
}
