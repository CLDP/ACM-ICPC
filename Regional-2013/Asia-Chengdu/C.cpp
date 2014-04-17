#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const long long INF = 1000000007;

int a[MAXN];
long long f[MAXN][MAXN];

int main() {
    int TT;
    cin >> TT;
    
    for (int times = 1; times <= TT; ++times) {
        long long n, k;
        cin >> n >> k;
        for (int i = 1; i <= k; ++i) cin >> a[i];
        memset(f, 0, sizeof(f));
        
        long long h = 0, l = 0, hind = 0;
        bool sat = true;
        for (int i = 1; i <= k; ++i) {
            if (a[i] > i) {
                if (a[i] > h) {
                    h = a[i];
                    hind = i;
                } else
                    sat = false;
            } else {
                if (a[i] > l)
                    l = a[i];
                else
                    sat = false;
            }
        }
        
        for (int i = 1; i <= l; ++i) {
            bool app = false;
            for (int j = 1; j <= k; ++j)
             if (a[j] == i) app = true;
            if (!app) sat = false;
        }
        
        if (!sat) {
            cout << "Case #" << times << ": " << 0 << endl;
            continue;
        }
        
        if (k == n) {
            cout << "Case #" << times << ": " << 1 << endl;
            continue;
        }
        
        h = max(h, l);
        h = max(k, h);
        hind = k;
        f[h][hind] = 1;
        for (int i = h + 1; i <= n; ++i) {
            long long sum = f[i-1][hind];
            f[i][hind] = sum;
            for (int j = hind + 1; j < i; ++j) {
                sum = (sum + f[i-1][j]) % INF;
                f[i][j] = sum;
            }
        }
        
        long long res = 0;
        for (int j = hind; j < n; ++j) res = (res + f[n][j]) % INF; 
        cout << "Case #" << times << ": " << res << endl;
    }
    
    return 0;
}
