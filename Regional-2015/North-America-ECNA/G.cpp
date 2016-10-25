#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

long long f[100][8];
bool z[100][3];

int main() {
    int N, M;
    cin >> N >> M;
    memset(f, 0, sizeof(f));
    memset(z, 0, sizeof(z));
    for (int i = 0; i < M; ++i) {
        double A, B;
        cin >> A >> B;
        z[(int)A][(int)B] = true;
    }
    f[0][7] = 1;
    for (int i = 0; i < N; ++i) {
        int M = 0;
        if (i != 0) {
            for (int j = 0; j < 3; ++j) {
                if (z[i - 1][j]) continue;
                M += (1 << j);
            }
        }

        // 0
        f[i + 1][0] = f[i][7];

        // 1
        if (!z[i][0]) {
            f[i + 1][1] += f[i][7];
            if (M & 1) f[i + 1][1] += f[i][7 - 1];
        } else {
            f[i + 1][1] = f[i + 1][0];
        }

        // 2
        if (!z[i][1]) {
            f[i + 1][2] += f[i][7];
            if (M & 2) f[i + 1][2] += f[i][7 - 2];
        } else {
            f[i + 1][2] = f[i + 1][0];
        }

        // 3
        if (!z[i][0] && !z[i][1]) {
            // two blocks + one block
            f[i + 1][3] += f[i][7] + f[i][7];
            if (M & 1) f[i + 1][3] += f[i][7 - 1];
            if (M & 2) f[i + 1][3] += f[i][7 - 2];
            if ((M & 2) && (M & 1)) f[i + 1][3] += f[i][7 - 3];
        } else {
            if (z[i][0]) {
                f[i + 1][3] = f[i + 1][2];
            } else {
                f[i + 1][3] = f[i + 1][1];
            }
        }

        // 4
        if (!z[i][2]) {
            f[i + 1][4] += f[i][7];
            if (M & 4) f[i + 1][4] += f[i][7 - 4];
        } else {
            f[i + 1][4] = f[i + 1][0];
        }

        // 5
        if (!z[i][0] && !z[i][2]) {
            f[i + 1][5] += f[i][7];
            if (M & 1) f[i + 1][5] += f[i][7 - 1];
            if (M & 4) f[i + 1][5] += f[i][7 - 4];
            if ((M & 1) && (M & 4)) f[i + 1][5] += f[i][7 - 5];
        } else {
            if (z[i][0]) {
                f[i + 1][5] = f[i + 1][4];
            } else {
                f[i + 1][5] = f[i + 1][1];
            }
        }

        // 6
        if (!z[i][1] && !z[i][2]) {
            f[i + 1][6] += f[i][7] + f[i][7];
            if (M & 2) f[i + 1][6] += f[i][7 - 2];
            if (M & 4) f[i + 1][6] += f[i][7 - 4];
            if ((M & 2) && (M & 4)) f[i + 1][6] += f[i][7 - 6];
        } else {
            if (z[i][1]) {
                f[i + 1][6] = f[i + 1][4];
            } else {
                f[i + 1][6] = f[i + 1][2];
            }
        }

        // 7
        if (!z[i][0] && !z[i][1] && !z[i][2]) {
            // three blocks + 2 two blocks
            f[i + 1][7] += f[i][7] + f[i][7] + f[i][7];
            if (M & 1) f[i + 1][7] += f[i][7 - 1] + f[i][7 - 1];
            if (M & 2) f[i + 1][7] += f[i][7 - 2];
            if (M & 4) f[i + 1][7] += f[i][7 - 4] + f[i][7 - 4];
            if ((M & 1) && (M & 2)) f[i + 1][7] += f[i][7 - 3];
            if ((M & 2) && (M & 4)) f[i + 1][7] += f[i][7 - 6];
            if ((M & 1) && (M & 4)) f[i + 1][7] += f[i][7 - 5];
            if (M == 7) f[i + 1][7] += f[i][0];
        } else {
            if (z[i][0]) {
                f[i + 1][7] = f[i + 1][6];
            } else 
            if (z[i][1]) {
                f[i + 1][7] = f[i + 1][5];
            } else {
                f[i + 1][7] = f[i + 1][3];
            }
        }
    }

    M = 0;
    for (int j = 0; j < 3; ++j) {
        if (z[N - 1][j]) continue;
        M += (1 << j);
    }

    cout << f[N][M] << endl;

    return 0;
}
