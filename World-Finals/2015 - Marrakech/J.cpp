#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;

const int MAXN = 500010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

typedef complex<double> cp;

int X[MAXN], f[MAXN][20], g[MAXN][20];

inline int dcmp(double a) {
    if (a < -EPS) return -1;
    return a > EPS;
}

void fft(int n, cp *x, cp *y, bool inv) {
    if (n == 1) {
        y[0] = x[0];
        return ;
    }
    cp *xeven = new cp[n / 2];
    cp *xodd  = new cp[n / 2];
    cp *yeven = new cp[n / 2];
    cp *yodd  = new cp[n / 2];
    cp w(1, 0), wn;

    if (inv) 
        wn = cp(cos(-2 * PI / n), sin(-2 * PI / n));
    else 
        wn = cp(cos( 2 * PI / n), sin( 2 * PI / n));

    for (int i = 0; i < n / 2; ++i) {
        xeven[i] = x[i * 2];
        xodd[i] = x[i * 2 + 1];
    }
    fft(n / 2, xeven, yeven, inv);
    fft(n / 2, xodd, yodd, inv);
    for (int i = 0; i < n / 2; ++i) {
        y[i]         = yeven[i] + w * yodd[i];
        y[i + n / 2] = yeven[i] - w * yodd[i];
        w *= wn;
    }
    delete[] xeven;
    delete[] yeven;
    delete[] xodd;
    delete[] yodd;
}

void PolyMulti(double *A, int na, double *B, int nb, double* &C, int &nc) {
    int n = max(na, nb);
    n = 1 << ((int) ceil(log(2 * n) / log(2) - EPS));
    cp *x  = new cp[n];
    cp *ya = new cp[n];
    cp *yb = new cp[n];
    cp *yc = new cp[n];

    for (int i = 0; i < n; ++i) x[i] = (i < na) ? A[i] : 0; 
    fft(n, x, ya, 0);

    for (int i = 0; i < n; ++i) x[i] = (i < nb) ? B[i] : 0; 
    fft(n, x, yb, 0);
    
    for (int i = 0; i < n; ++i) yc[i] = ya[i] * yb[i]; 
    fft(n, yc, x, 1);
    
    C = new double[n];
    for (int i = 0; i < n; ++i) C[i] = x[i].real() / n;

    while (n > 0 && dcmp(C[n - 1]) == 0) --n;
    nc = n;
    delete[] x; 
    delete[] ya; 
    delete[] yb; 
    delete[] yc;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N = 500000;
    for (int i = 1; i <= N; ++i) {
        int j = i;
        while (j <= N) {
            ++X[j];
            j += i;
        }
    }

    double *A = new double[N];
    double *B = new double[N];
    for (int i = 0; i < N; ++i) A[i] = B[i] = X[i + 1];

    int M = 0;
    double *C;
    PolyMulti(A, N, B, N, C, M);
    g[1][0] = 1;
    for (int i = 2; i <= N; ++i) {
        f[i][0] = round(C[i - 2]);
        g[i][0] = i;
    }
    delete[] A;
    delete[] B;
    delete[] C;

    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (j + (1 << (i - 1)) <= N && f[j][i - 1] < f[j + (1 << (i - 1))][i - 1]) {
                f[j][i] = f[j + (1 << (i - 1))][i - 1];
                g[j][i] = g[j + (1 << (i - 1))][i - 1];
            } else {
                f[j][i] = f[j][i - 1];
                g[j][i] = g[j][i - 1];
            }
        }
    }

    int a, b;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        int j = 0;
        while (a + (1 << (j + 1)) < b) ++j;
        if (f[a][j] < f[b + 1 - (1 << j)][j]) {
            cout << g[b + 1 - (1 << j)][j] << " " << f[b + 1 - (1 << j)][j] << endl;
        } else {
            cout << g[a][j] << " " << f[a][j] << endl;
        }
    }

    return 0;
}
