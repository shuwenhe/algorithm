#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int max_expression_value(vector<int>& a) {
    int n = a.size();
    int max_val = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    if (i != j && i != k && i != l && j != k && j != l && k != l) {
                        int value = abs(a[i] - a[j]) + abs(a[j] - a[k]) + abs(a[k] - a[l]) + abs(a[l] - a[i]);
                        max_val = max(max_val, value);
                    }
                }
            }
        }
    }

    return max_val;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        cout << max_expression_value(a) << endl;
    }

    return 0;
}

