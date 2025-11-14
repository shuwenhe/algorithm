#include <iostream>
using namespace std;

const int MAXN = 105;
char field[MAXN][MAXN];
int n, m;

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || field[x][y]!= 'W') return;
    field[x][y] = '.';
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i!= 0 || j!= 0) dfs(x + i, y + j);
        }
    }
}

int countPonds() {
    int ponds = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == 'W') {
                ponds++;
                dfs(i, j);
            }
        }
    }
    return ponds;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> field[i][j];
        }
    }
    cout << countPonds() << endl;
    return 0;
}