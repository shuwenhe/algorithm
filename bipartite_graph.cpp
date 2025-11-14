#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std; 

const int maxN = 20001, maxM = maxN * 4;

struct edge {
    edge* next;
    int t;
} *v[maxN], e[maxM];

int n;
int ec;
int mat[maxN];
int stack[maxN];
int s[maxN][2];
int deg[maxN];
bool nuked[maxN];

inline void addEdge(int a, int b) {
    e[++ec].next = v[a];
    v[a] = e + ec;
    v[a]->t = b;

    e[++ec].next = v[b];
    v[b] = e + ec;
    v[b]->t = a;

    ++deg[b];
    mat[b] = a;
}

void init() {
    ifstream fin("transform.in");
    fin >> n;

    int i, d, t1, t2;

    for (i = 1; i <= n; ++i) {
        fin >> d;

        t1 = i + d;
        if (t1 > n){
		t1 -= n;
	} 

        t2 = i - d;
        if (t2 < 1){
		t2 += n;
	} 

        if (t1 < t2){
		s[i][0] = t1;
		s[i][1] = t2;
	}else{
		s[i][0] = t2;
		s[i][1] = t1;
	}

        addEdge(i, s[i][1] += n);
        addEdge(i, s[i][0] += n);
        deg[i] = 2;
    }

    fin.close();
}

void noAnswer() { 
	printf("No Answer\n"); 
	exit(0); 
}

inline void match(int i,int j) {
	mat[i] = j; 
	mat[j] = i; 
}

void prune() { 
	int stop = 0,i,j; 

	for (i = 1;i <= n; i++) { 
		if (deg[i + n] == 0){
			noAnswer(); 
		}else if(deg[i + n] == 1){
			stack[++stop] = i + n; 
		}
	}

	while(stop){ 
		i = stack[stop--]; 
		nuked[i] = true; 

		for (edge *e=v[i];e;e=e->next) { 
			j = e->t; 
			if (!nuked[j]){
				break; 
			} 
		} 

		match(i,j); 
		i = j; 
		nuked[i] = true; 

		for (edge *e=v[i];e;e=e->next) { 
			j = e->t; 
			if (!nuked[j]) { 
				deg[j]--; 
				if(deg[j] == 0){
					noAnswer(); 
				}else if(deg[j] == 1){
					stack[++stop] = j; 
				} 
			} 
		} 
	} 
}

void dfs(int i,bool s) { 
	nuked[i] = true; 
	int j; 

	for (edge *e=v[i];e;e=e->next) { 
		j = e->t; 
		if(!nuked[j]){ 
			dfs(j,!s); 
			if(s){
				match(i,j); 
			}
			break; 
		} 
	} 
}

void solve() { 
	prune(); 
	for (int i=1;i <= n;i++) { 
		if (!nuked[i]){
			dfs(i,true); 
		} 
	}
}

void print() {
    ofstream fout("transform.out");

    int i;
    for(i = 1; i < n; i++){
	    fout << mat[i] - n - 1 << " ";
    }

    fout << mat[i] - n - 1 << "\n";
    fout.close();
}

int main() {
    init();
    solve();
    print();
    return 0;
}
