#include <iostream>
#include <vector>

using namespace std;

int main(){
	int l,m;
	cin>>l>>m;
	vector<bool> covered(l + 1,false);

	for(int i = 0; i < m; i++){
		int u,v;
		cin>>u>>v;
		for(int j = u; j <= v; j++){
			covered[j] = true;
		}
	}
	int count = 0;
	for(int i = 1; i <= l; i++){
		if(!covered[i]){
			count++;
		}
	}
	cout<<count<<endl;
	return 0;
}
