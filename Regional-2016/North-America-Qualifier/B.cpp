#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1020;


double A[MAXN][MAXN]; // The matrix
double x[MAXN];       // The solutions

void A_clear(int M, int k) {
    for (int i = k; i < M; ++i) {
        double temp = 0;
        for (int j = k; j <= M; ++j) temp = max(temp, fabs(A[i][j]));
        for (int j = k; j <= M; ++j) A[i][j] /= temp;
        for (int j = k; j <= M; ++j) 
         if (fabs(A[i][j]) < 1e-8) A[i][j] = 0;
    }
}


int Gauss(int M) {
    for (int i = 0; i < M; ++i) {
        A_clear(M, i);
        int j = i;
        while (A[j][i] == 0) ++j;
        for (int k = i; k <= M; ++k) swap(A[j][k], A[i][k]);
        
        for (int k = i + 1; k < M; ++k) {
            if (A[k][i] == 0) continue;
            double T = A[i][i] / A[k][i];
            for (int l = i; l <= M; ++l) {
                A[k][l] = A[k][l] * T - A[i][l];
            }
        }
    }
    
    for (int i = M - 1; i >= 0; --i) {
        x[i] = A[i][M];
        for (int j = i + 1; j < M; ++j) x[i] -= x[j] * A[i][j];
        x[i] /= A[i][i];
    }
    return 0;
}

int X[MAXN];
double P[MAXN][5];


int main() {
    int N, M;
    cin >> N;
    M = N * (N + 1) / 2;
    for (int i = 0; i < M; ++i) cin >> X[i];
    for (int i = 0; i < M; ++i)
     for (int j = 0; j < 5; ++j) cin >> P[i][j];
    
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= i; ++j) {
         int curr = i * (i - 1) / 2 + j - 1;
         int TL, TR, BL, BR;
         TL = TR = BL = BR = -1;
         if (j > 1) TL = (i - 1) * (i - 2) / 2 + j - 2;
         if (j < i) TR = (i - 1) * (i - 2) / 2 + j - 1;
         if (i < N) {
             BL = i * (i + 1) / 2 + j - 1;
             BR = i * (i + 1) / 2 + j;
         }
         A[curr][curr] = 1;
         if (TL != -1) A[curr][TL] = -P[curr][0];
         if (TR != -1) A[curr][TR] = -P[curr][1];
         if (BL != -1) A[curr][BL] = -P[curr][2];
         if (BR != -1) A[curr][BR] = -P[curr][3];
         A[curr][M] = P[curr][4] * X[curr];
     }
     
    Gauss(M);
    printf("%.10lf\n", x[0]);
    
    return 0;
}
