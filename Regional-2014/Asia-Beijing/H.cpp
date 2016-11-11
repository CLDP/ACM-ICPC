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

int M2[22];
int f[2][2000010];
int x[1000010];

int main() {
    int times;
    cin >> times;
    M2[0] = 1;
    for (int i = 1; i < 22; ++i) M2[i] = M2[i - 1] + M2[i - 1];
    
    for (int tt = 1; tt <= times; ++tt) {
        int N, M, A = 0;
        cin >> N >> M;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &x[i]);
            A = max(A, x[i]);
        }
        
        int MM = 0;
        while (M2[MM] <= A) ++MM;
        MM = M2[MM];
        
        for (int i = 0; i < MM; ++i) f[0][i] = f[1][i] = 0;
        bool T = false;
        f[0][x[0]] = 1;
        f[0][0] = 1;
        for (int i = 1; i < N; ++i) {
            T = !T;
            for (int j = 0; j < MM; ++j) f[T][j] = f[!T][j] + f[!T][j ^ x[i]];
        }
        long long ans = 0;
        for (int j = M; j < MM; ++j) ans += f[T][j];
        printf("Case #%d: %I64d\n", tt, ans);
    }
    return 0;
}
