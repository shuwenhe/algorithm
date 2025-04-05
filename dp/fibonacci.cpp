#include <iostream>

using namespace std;

int fibonacci(int n){
	if(n <= 1){
		return n;
	}
	return 0;
}

int main(){
	int n;
	cout<<"Please input nubmer n"<<endl;
	cin>>n;
	cout<<"fibonacci number equal: "<<fibonacci(n)<<endl;
}
