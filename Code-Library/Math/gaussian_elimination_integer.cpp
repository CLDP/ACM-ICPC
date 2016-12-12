const int MAXN = 210;

int A[MAXN][MAXN];
int X[MAXN];

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void clear(int b[], int M) {
    int k = 0;
    bool flag = false;
    for (int i = 0; i < M; ++i) {
        if (b[i] == 0) continue;
        if (flag) {
            k = gcd(b[i], k);
        } else {
            k = b[i];
            flag = true;
        }
    }
    if (k == 0) return ;
    for (int i = 0; i < M; ++i) b[i] /= k;
}

// Gaussian Elimination
// sum A[i][j] * X[j] = A[i][M]
// N equations, M variables
// Indices start from 0
// return 0 if no solution, otherwise 1
// return arbitrary solution if infinitely many
int gauss(int N, int M) {
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
                for (int k = 0; k <= M; ++k) A[j][k] = A[j][k] * A[r][i] - temp * A[r][k];
                clear(A[j], M + 1);
            }
        }
        ++r;
    }
    for (int i = 0; i < N; ++i) {
        if (!A[i][M]) continue;
        int j = 0;
        while (j < M && !A[i][j]) ++j;
        if (j == M) return 0;
        X[j] = A[i][M] / A[i][j];
    }
    return 1;
}
