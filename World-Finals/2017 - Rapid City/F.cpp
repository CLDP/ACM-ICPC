#include <iostream>
using namespace std;

const int MAXN = 300;
const long long INF = 1LL * 1000000000 * 1000000000;

int x[MAXN], y[MAXN];
long long f[MAXN][MAXN], g[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) cin >> x[i] >> y[i];
    for (int i = 1; i <= N; ++i) {
        int P = x[i];
        for (int j = i; j <= N; ++j) {
            g[i][j] = INF;
            while (true) {
                long long temp = 0;
                for (int k = i; k <= j; ++k) temp += 1LL * y[k] * (x[k] - P) * (x[k] - P);
                if (temp < g[i][j]) {
                    g[i][j] = temp;
                    ++P;
                } else {
                    --P;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= N; ++i) f[i][0] = INF;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= min(M, i); ++j) {
            f[i][j] = f[i][j - 1];
            for (int k = j - 1; k <= i; ++k) {
                f[i][j] = min(f[i][j], f[k][j - 1] + g[k + 1][i]);
            }
        }
    }
    cout << f[N][M] << endl;

    return 0;
}
