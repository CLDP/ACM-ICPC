#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct node {
    int a, b, c, d;
    string name;
    
    bool operator < (node const &B) const {
        return name < B.name;
    }
};

int x[2][12][12][20];
bool y[12][12];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        vector<node> X(N);
        for (int i = 0; i < N; ++i) cin >> X[i].name >> X[i].a >> X[i].b >> X[i].c >> X[i].d;
        sort(X.begin(), X.end());
        
        cout << "Case Number " << ++times << endl;
        if (N == 1) {
            cout << "   " << X[0].name << "   0" << endl;
            continue;
        }
        
        memset(y, 0, sizeof(y));
        memset(x, 0, sizeof(x));
        for (int k = 0; k < N; ++k) {
            for (int i = X[k].a; i <= X[k].c; ++i)
             for (int j = X[k].b; j <= X[k].d; ++j) {
                 for (int l = 0; l < N; ++l) x[0][i][j][l] = 0;
                 y[i][j] = true;
                 x[0][i][j][k] = 1000000;
             }
        }
        
        bool odd = true;
        int ans = 0;
        vector<bool> z(N, false);
        
        int left = N;
        while (left > 0) {
            ++ans;
            for (int k = 0; k < N; ++k) {
                int total = 0;
                for (int i = X[k].a; i <= X[k].c; ++i)
                 for (int j = X[k].b; j <= X[k].d; ++j) {
                     int sub_total = 0;
                     for (int l = 0; l < N; ++l) {
                         x[odd][i][j][l] = x[!odd][i][j][l] - x[!odd][i][j][l] / 1000 * 
                                           (y[i - 1][j] + y[i + 1][j] + y[i][j - 1] + y[i][j + 1]);
                         x[odd][i][j][l] += x[!odd][i - 1][j][l] / 1000 + x[!odd][i + 1][j][l] / 1000
                                          + x[!odd][i][j - 1][l] / 1000 + x[!odd][i][j + 1][l] / 1000;
                         if (x[odd][i][j][l] > 0) ++sub_total;
                     }
                     if (sub_total == N) ++total;
                 }
                if (total == (X[k].c - X[k].a + 1) * (X[k].d - X[k].b + 1)) {
                    if (!z[k]) {
                        z[k] = true;
                        cout << "   " << X[k].name << "   " << ans << endl; 
                        --left;
                    }
                }
            }
            odd = !odd;
        }
    }

    return 0;
}
