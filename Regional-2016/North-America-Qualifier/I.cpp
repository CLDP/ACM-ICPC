#include <iostream>
using namespace std;

const int MAXN = 410;

int A[MAXN][MAXN];
int X[MAXN];

int extended_euclidean(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int res = extended_euclidean(b, a % b, y, x);
    y -= a / b * x;
    return res;
}

int modular(int x, int m) {
    if (x < 0) x += abs(x / m) * m + m;
    return x % m;
}

int modular_inverse(int a, int m) {
    int x, y;
    extended_euclidean(a, m, x, y);
    return modular(x, m);
}

int gauss(int N, int M, int mod) {
    for (int i = 0, r = 0; i < M; ++i) {
        int j = r;
        while (j < N && !A[j][i]) ++j;
        if (j >= N) continue;
        if (j > r) {
            for (int k = 0; k <= M; ++k) swap(A[r][k], A[j][k]);
        }
        for (j = 0; j < N; ++j) {
            if (j != r && A[j][i]) {
                int temp = A[j][i];
                for (int k = 0; k <= M; ++k) 
                    A[j][k] = modular(A[j][k] * A[r][i] - temp * A[r][k], mod);
            }
        }
        ++r;
    }

    for (int i = 0; i < N; ++i) {
        if (!A[i][M]) continue;
        int j = 0;
        while (j < M && !A[i][j]) ++j;
        if (j == M) return 0;
        X[j] = modular(A[i][M] * modular_inverse(A[i][j], mod), mod);
    }
    return 1;
}


int main() {
    int N, M, mod;
    cin >> N >> M >> mod;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int R = i * M + j, B;
            cin >> B;
            A[R][N * M] = mod - B;
            for (int k = 0; k < N; ++k) A[R][k * M + j] = 1;
            for (int k = 0; k < M; ++k) A[R][i * M + k] = 1;
        }
    }

    if (gauss(N * M, N * M, mod)) {
        int ans = 0;
        for (int i = 0; i < N * M; ++i) ans += X[i];
        cout << ans << endl;
        for (int i = 0; i < N * M; ++i) {
            while (X[i]--) cout << i + 1 << " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
