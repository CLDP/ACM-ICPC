#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;

int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int n, l ,t;
        cin >> n >> l >> t;
        double u[2][n];
        double e[n][n];
        double a, b, c;
        double f[n];
        int i, j, k;
        for (i = 0; i < n; ++i) {
            cin >> u[0][i];
            u[1][i] = 0;
        }
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) e[i][j] = 0;
            e[i][i] = 1;
        }
        for (i = 0; i < l; ++i) {
            cin >> j >> k >> a;
            e[j][j] = e[j][j] - a;
            e[j][k] += a;
        }
        k = 0;
        while (t > 0) {
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    u[1-k][j] += u[k][i] * e[i][j];
                }
                u[k][i] = 0;
            }
            k = 1 - k;
            --t;
        }
        for (i = 0; i < n; ++i) {
            f[i] = 0;
            for (j = 0; j < n; ++j) {
                if ((e[i][j] > 0 || e[j][i] > 0) || (i == j))
                    f[i] += u[k][j];
            }
        }
        double min = f[0];
        for (i = 1; i < n; ++i)
            if (f[i] < min) min = f[i];
        printf("%.9lf\n", min);
    }
    
    return 0;
}
