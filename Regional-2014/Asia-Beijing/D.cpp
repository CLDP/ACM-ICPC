#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[205];
int b[205];
long long f[205][205];

int main() {
    int t;
    
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt) {
        int n;
        scanf("%d", &n);
        
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
        a[n + 1] = 0;
        b[n + 1] = 0;
        for (int i = 1; i <= n; ++i) f[i][i] = a[i] + b[i - 1] + b[i + 1];
        for (int dis = 1; dis < n; ++dis)
            for (int i = 1; i + dis <= n; ++i) {
                int j = i + dis;
                f[i][j] = b[i - 1] + b[j + 1];
                long long best = a[i] + f[i + 1][j];
                for (int k = i + 1; k <= j; ++k)
                    best = min(best, a[k] + f[i][k - 1] + f[k + 1][j]);
                f[i][j] += best;
            }
        printf("Case #%d: %d\n", tt, f[1][n]);
    }

    return 0;
}
