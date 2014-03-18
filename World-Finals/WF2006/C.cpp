#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-6;
const int MAXN = 101;
const int MAXE = 300;

int N, M, R;
double x[MAXN], y[MAXN], z[MAXN], A[MAXE][MAXN], B[MAXE][MAXN];

bool gauss() {
    int L = 0;
    for (int i = M; i; --i) {
        int k = L;
        for (int j = L + 1; j < R; ++j)
         if (fabs(B[j][i]) > fabs(B[k][i])) k = j;
        if (fabs(B[k][i]) < EPS) continue;
        memcpy(x, B[L], sizeof(x));
        memcpy(B[L], B[k], sizeof(x));
        memcpy(B[k], x, sizeof(x));
        
        for (int j = L + 1; j < R; ++j) {
            double c = B[j][i] / B[L][i];
            for (k = 0; k < i; ++k) B[j][k] -= c * B[L][k];
            B[j][i] = 0;
        }
        ++L;
    }
    for (int i = L; i < R; ++i)
     if (fabs(B[i][0]) > EPS) return false;
    return true;
}

int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        
        memset(A, 0, sizeof(A));
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> z[i];
        
        for (int i = 1; i <= M; ++i) {
            int j, k;
            cin >> j >> k;
            --j;
            --k;
            
            if (z[j]) {
                A[3*j][i] = x[k] - x[j];
                A[3*j+1][i] = y[k] - y[j];
                A[3*j+2][i] = z[k] - z[j];
            }
            if(z[k]) {
                A[3*k][i] = x[j] - x[k];
                A[3*k+1][i] = y[j] - y[k];
                A[3*k+2][i] = z[j] - z[k];
            }
        }
        
        R = 0;
        for (int i = 0; i < N; ++i)
         if (z[i]) {
             memcpy(B[R++], A[i*3], sizeof(x));
             memcpy(B[R++], A[i*3+1], sizeof(y));
             memcpy(B[R++], A[i*3+2], sizeof(z));
             B[R - 1][0] = 1;
         }
        
        cout << "Sculpture " << ++times << ": ";
        if (!gauss()) {
            cout << "NON-STATIC" << endl;
            continue;
        }
        
        R = 0;
        for (int i = 0; i < N; ++i)
         if (z[i]) {
             memcpy(B[R++], A[i*3], sizeof(x));
             memcpy(B[R++], A[i*3+1], sizeof(y));
             memcpy(B[R++], A[i*3+2], sizeof(z));
             B[R - 1][0] = sin(double(i*3+1));
             B[R - 2][0] = sin(double(i*3+2));
             B[R - 3][0] = sin(double(i*3+3));
         }
        if (!gauss()) {
            cout << "UNSTABLE" << endl;
            continue;
        }
        cout << "STABLE" << endl;
    }
    return 0;
}
