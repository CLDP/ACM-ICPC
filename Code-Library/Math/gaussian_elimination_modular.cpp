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

// a and m must be relatively prime
// return x such that ax = 1 mod m
int modular_inverse(int a, int m) {
    int x, y;
    extended_euclidean(a, m, x, y);
    return modular(x, m);
}

// Gaussian Elimination
// sum A[i][j] * X[j] = A[i][M]
// N equations, M variables
// Indices start from 0
// return 0 if no solution, otherwise 1
// return arbitrary solution if infinitely many
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
