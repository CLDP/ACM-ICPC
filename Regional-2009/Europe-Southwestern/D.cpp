#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 22;
const int C[MAXN] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20, 1};

double f[510][510][2];
int z[510][510][2];

double dp(int a, int b, bool c) {
    if (z[a][b][c]) return f[a][b][c];
    z[a][b][c] = true;
    f[a][b][c] = 0;
    if (a == 0) return f[a][b][c] = 1;
    if (b == 0) return f[a][b][c] = 0;
    if (c == 0) {
        double temp = 0;
        for (int i = 0; i < 20; ++i) {
            if (a >= C[i]) {
                temp += dp(a - C[i], b, !c);
            } else {
                temp += dp(a, b, !c);
            }
        }
        f[a][b][c] = temp / 20;
    } else {
        double big_temp = 1;
        for (int i = 1; i <= 20; ++i) {
            double temp = 0;
            for (int j = -1; j <= 1; ++j) {
                if (b >= C[i + j]) {
                    temp += dp(a, b - C[i + j], !c);
                } else {
                    temp += dp(a, b, !c);
                }
            }
            temp /= 3;
            if (temp < big_temp) big_temp = temp;
        }
        f[a][b][c] = big_temp;
    }
    return f[a][b][c];
}



int main() {
    for (int i = 1; i < 20; ++i) {
        f[0][i][0] = f[0][i][1] = 1;
        f[i][0][0] = f[i][0][1] = 0;
        z[0][i][0] = z[0][i][1] = z[i][0][0] = z[i][0][1] = true;
    }
    
    for (int i = 1; i < 20; ++i)
     for (int j = 1; j < 20; ++j) {
         z[i][j][0] = z[i][j][1] = true;
         
         int PP;
         f[i][j][1] = 1;
         for (int k = 1; k <= 20; ++k) {
             double mark = 0, temp = 0;
             for (int l = -1; l <= 1; ++l) {
                 if (C[k + l] > j) {
                     for (int p = 0; p < 20; ++p) {
                         if (C[p] > i) continue;
                         temp += 1.0 / 60;
                         mark += 1.0 / 60 * f[i - C[p]][j][1];
                     }
                     continue;
                 }
                 temp += 1.0 / 3;
                 mark += 1.0 / 3 * f[i][j - C[k + l]][0];
             }
             if (mark / temp < f[i][j][1]) {
                 f[i][j][1] = mark / temp;
                 PP = k;
             }
         }
         
         double temp = 0;
         for (int k = 0; k < 20; ++k) {
             if (C[k] > i) {
                 for (int l = -1; l <= 1; ++l) {
                     if (C[PP + l] > j) continue;
                     temp += 1.0 / 60;
                     f[i][j][0] += 1.0 / 60 * f[i][j - C[PP + l]][0];
                 }
                 continue;
             }
             temp += 0.05;
             f[i][j][0] += f[i - C[k]][j][1] * 0.05;
         }
         f[i][j][0] /= temp;
     }
     
    int N;
    while (cin >> N) {
        if (N == 0) break;
        printf("%.11lf %.11lf\n", dp(N, N, 0), 1 - dp(N, N, 1));
    }
    return 0;
}
