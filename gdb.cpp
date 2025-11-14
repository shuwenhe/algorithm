#include<iostream>

using namespace std;

int gdb(int a,int b){
	while(b != 0){
		int temp = a%b;
		a = b;
		b = temp;
	}
	return a;	
}

int main(){
	int a,b;
	cin>>a>>b;
	cout<<gdb(a,b);
}
