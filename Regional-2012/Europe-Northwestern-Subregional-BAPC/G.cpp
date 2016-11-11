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

int s[160];
long double p[160];
long double f[160][160];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        for (int i = 0; i < n; ++i) {
            cin >> s[i] >> p[i];
            p[i] = p[i] / 100;
        }
        
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j <= 150; ++j) {
                f[i + 1][j] = f[i][j];
                if (j >= s[i])
                    f[i + 1][j] = max(f[i + 1][j], f[i][j - s[i]] * p[i]);
            }
        
        long double res = 0;
        for (int i = 76; i <= 150; ++i)
            res = max(res, f[n][i]);
        
        double rr = res * 100;
        printf("%.8lf\n", rr);
    }

    return 0;
}
