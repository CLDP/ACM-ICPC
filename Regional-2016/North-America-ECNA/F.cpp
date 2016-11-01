#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const int INF = 1000000000;

int N;
int X[MAXN], Y[MAXN][MAXN];
int f[MAXN][MAXN];

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int dp(int a, int b, int c) {
    if (f[a][b] > 0) return f[a][b];
    if (a + 1 == b) {
        if (a + N - 1 == b) return f[a][b] = Y[a][b];
        return 0;
    }

    f[a][b] = INF;
    for (int i = a + 1; i < b; ++i) {
        int T = dp(a, i, 0) + dp(i, b, 0);
        if (a + N - 1 == b) {
            T += 2 * min(Y[a][b], min(Y[a][i], Y[i][b]));
        } else {
            T += Y[a][b];
        }
        f[a][b] = min(f[a][b], T);
    }
    return f[a][b];
}

int main() {
    while (cin >> N) {
        if (N == 0) break;

        for (int i = 1; i <= N; ++i) {
            cin >> X[i];
            X[i + N] = X[i];
        }

        for (int i = 1; i <= N + N; ++i) 
         for (int j = i + 1; j <= N + N; ++j) {
             f[i][j] = 0;
             Y[i][j] = gcd(X[i], X[j]);
         }

        int ans = dp(1, N, 1);
        for (int i = 2; i <= N; ++i) ans = min(ans, dp(i, i + N - 1, 1));
        cout << ans << endl;
    }
    return 0;
}
