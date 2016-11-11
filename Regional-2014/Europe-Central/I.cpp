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

int x[100100];
bool y[100100];

int compare(long long A1, long long B1, long long A2, long long B2) {
    if (A1 * B2 == A2 * B1) return 0;
    if (A1 * B2 > A2 * B1) return -1;
    return 1;
}

int main() {
    int times;
    cin >> times;
    while (times--) {
        int N;
        scanf("%d", &N);
        long long B = 0, W = 0;
        for (int i = 0; i < N; ++i) {
            char c;
            scanf("%d %c", &x[i], &c);
            if (c == 'B') {
                y[i] = true;
                B += x[i];
            } else {
                y[i] = false;
                W += x[i];
            }
        }
        if (B == 0 || W == 0) {
            int ans = 0;
            for (int i = 0; i < N; ++i) ans += x[i];
            printf("%d\n", ans);
            continue;
        }
        long long BB = 0, WW = 0, ans = 0;
        for (int i = 0; i < N; ++i) {
            long long BBB = BB, WWW = WW;
            if (y[i]) BBB += x[i]; else WWW += x[i];
            if (BBB == 0 || WWW == 0) {
                BB = BBB;
                WW = WWW;
                continue;
            }
            
            if (y[i]) {
                if (B * WW % W == 0 && BB < B * WW / W && B * WW / W <= BBB) ++ans;
            } else {
                if (W * BB % B == 0 && WW < W * BB / B && W * BB / B <= WWW) ++ans;
            }
            BB = BBB;
            WW = WWW;
        }
        cout << ans << endl;
    }
    return 0;
}
