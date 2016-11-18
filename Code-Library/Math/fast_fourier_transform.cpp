#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);

typedef complex<double> cp;

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

// N = sum_{i=0}^{n-1} A[i] * 10^i
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

// C[k] = sum_{i=0}^{n-1} A[i] * B[i - k], circular
void convolution(double *A, double *B, double* &C, int n) {
    double *D = new double[n];
    D[0] = B[0];
    for (int i = 1; i < n; ++i) D[i] = B[n - i];
    int m = 0;
    PolyMulti(A, n, D, n, C, m);
    for (int i = 0; i < n; ++i) C[i] += C[i + n];
    delete[] D;
}
