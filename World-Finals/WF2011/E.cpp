#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2100;

int x[MAXN][MAXN];
int s[MAXN][MAXN];
int u[MAXN][MAXN];


int main() {
    int N, M, P, Q, times = 0;
    while (cin >> N >> M >> P >> Q) {
        if (N + M + P + Q == 0) break;
        memset(s, 0, sizeof(s));
        memset(x, 0, sizeof(x));
        for (int i = 0; i < P; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            ++x[a + b - 1][a - b + M];
        }
        
        for (int i = 1; i <= N + M - 1; ++i)
         for (int j = 1; j <= N + M - 1; ++j) {
             u[i][j] = u[i - 1][j] + x[i][j];
             s[i][j] = s[i][j - 1] + u[i][j];
         }
        
        
        cout << "Case " << ++times << ":" << endl;
        for (int k = 0; k < Q; ++k) {
            int L;
            cin >> L;
            int ans = -1, a, b;
            
            for (int j = 1; j <= M; ++j)
             for (int i = 1; i <= N; ++i) {
                 int temp = 0;
                 int A = i + j - 1, B = i - j + M;
                 temp += s[min(A + L, N + M - 1)][min(B + L, N + M - 1)];
                 temp -= s[max(A - L - 1, 0)][min(B + L, N + M - 1)];
                 temp -= s[min(A + L, N + M - 1)][max(B - L - 1, 0)];
                 temp += s[max(A - L - 1, 0)][max(B - L - 1, 0)];
                 if (temp > ans) {
                     ans = temp;
                     a = i;
                     b = j;
                 }
             }
            cout << ans << " (" << a << "," << b << ")" << endl;
        }
    }
    return 0;
}
