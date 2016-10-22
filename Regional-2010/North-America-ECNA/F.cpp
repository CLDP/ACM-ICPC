#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 110;

double NN[MAXN], I[MAXN], D[MAXN];
int C[MAXN][MAXN], F[MAXN][MAXN];


int main() {
    int M, N, times = 0;
    while (cin >> M >> N) {
        ++times;
        if (M == 0 && N == 0) break;
        for (int i = N - 1; i >= 0; --i) {
            cin >> NN[i] >> I[i] >> D[i];
        }

        for (int i = 0; i <= M; ++i) {
            for (int j = 0; j < N; ++j) {
                double P = I[j] + (i / (10.1 + i)) * D[j];
                P /= 100;
                C[i][j + 1] = round(P * NN[j]);
            }
        }

        memset(F, 0, sizeof(F));
        for (int i = 0; i <= M; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k <= i; ++k) {
                    F[i][j + 1] = max(F[i][j + 1], F[i - k][j] + C[k][j + 1]);
                }
            }
        }

        cout << "Case " << times << ": " << F[M][N] << endl;

        for (int i = N; i >= 1; --i) {
            for (int j = M; j >= 0; --j) {
                if (F[M - j][i - 1] + C[j][i] == F[M][i]) {
                    cout << N - i << ":" << j;
                    M -= j;
                    break;
                }
            }
            if (i == 1) cout << endl; else cout << " ";
        }
    }
    return 0;
}
