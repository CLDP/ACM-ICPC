const int MAXN = 210;
const double EPS = 1e-8;

double A[MAXN][MAXN];
double X[MAXN];

int dcmp(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
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
        while (j < N && !dcmp(A[j][i])) ++j;
        if (j >= N) continue;
        if (j > r) {
            for (int k = 0; k <= M; ++k) swap(A[r][k], A[j][k]);
        }
        for (j = 0; j < N; ++j) {
            if (j != r && dcmp(A[j][i])) {
                double temp = A[j][i] / A[r][i];
                for (int k = 0; k <= M; ++k) A[j][k] -= temp * A[r][k];
            }
        }
        ++r;
    }
    for (int i = 0; i < N; ++i) {
        if (!dcmp(A[i][M])) continue;
        int j = 0;
        while (j < M && !dcmp(A[i][j])) ++j;
        if (j == M) return 0;
        X[j] = A[i][M] / A[i][j];
    }
    return 1;
}
