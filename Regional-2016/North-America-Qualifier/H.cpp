#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110000;
const int INF = 1000000007;

int f[MAXN], g[MAXN];

int main() {
    for (int i = 1; i < MAXN; ++i) f[i] = g[i] = INF;
    int H, B, SH = 0, SB = 0;
    cin >> H;
    for (int i = 0; i < H; ++i) {
        int a;
        cin >> a;
        for (int j = SH; j >= 0; --j) {
            f[j + a] = min(f[j + a], f[j] + 1);
        }
        SH += a;
    }
    cin >> B;
    for (int i = 0; i < B; ++i) {
        int a;
        cin >> a;
        for (int j = SB; j >= 0; --j) {
            g[j + a] = min(g[j + a], g[j] + 1);
        }
        SB += a;
    }
    
    int ans = INF;
    for (int i = 1; i < MAXN; ++i) {
        ans = min(ans, f[i] + g[i]);
    }
    if (ans == INF) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }
    
    return 0;
}
