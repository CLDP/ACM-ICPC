#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int x[10][10][10];
int y[6][10][10];


int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 6; ++j) {
                string P;
                cin >> P;
                for (int k = 0; k < N; ++k)
                 if (P[k] == '.') y[j][i][k] = 0; else y[j][i][k] = P[k] - 'A' + 1;
            }
        }
        
        memset(x, 0, sizeof(x));
        
        for (int i = 0; i < N; ++i) 
         for (int j = 0; j < N; ++j) {
             if (y[0][i][j] == 0 || y[2][i][N - j - 1] == 0) {
                 for (int k = 0; k < N; ++k) x[i][j][k] = -1;
             }
             if (y[1][i][j] == 0 || y[3][i][N - j - 1] == 0) {
                 for (int k = 0; k < N; ++k) x[i][k][N - 1 - j] = -1;
             }
             if (y[4][i][j] == 0 || y[5][N - 1 - i][j] == 0) {
                 for (int k = 0; k < N; ++k) x[k][j][N - 1 - i] = -1;
             }
         }
         
        bool flag = true;
        while (flag) {
            flag = false;
            for (int i = 0; i < N; ++i)
             for (int j = 0; j < N; ++j) {
                 if (y[0][i][j] != 0) {
                     for (int k = 0; k < N; ++k) {
                         if (x[i][j][k] == -1) continue;
                         if (x[i][j][k] == 0) {
                             x[i][j][k] = y[0][i][j];
                             flag = true;
                         }
                         if (x[i][j][k] == y[0][i][j]) {
                             break;
                         } else {
                             x[i][j][k] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
                 
                 if (y[1][i][j] != 0) {
                     for (int k = 0; k < N; ++k) {
                         if (x[i][k][N - 1 - j] == -1) continue;
                         if (x[i][k][N - 1 - j] == 0) {
                             x[i][k][N - 1 - j] = y[1][i][j];
                             flag = true;
                         }
                         if (x[i][k][N - 1 - j] == y[1][i][j]) {
                             break;
                         } else {
                             x[i][k][N - 1 - j] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
                 if (y[2][i][j] != 0) {
                     for (int k = N - 1; k >= 0; --k) {
                         if (x[i][N - 1 - j][k] == -1) continue;
                         if (x[i][N - 1 - j][k] == 0) {
                             x[i][N - 1 - j][k] = y[2][i][j];
                             flag = true;
                         }
                         if (x[i][N - 1 - j][k] == y[2][i][j]) {
                             break;
                         } else {
                             x[i][N - 1 - j][k] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
                 
                 if (y[3][i][j] != 0) {
                     for (int k = N - 1; k >= 0; --k) {
                         if (x[i][k][j] == -1) continue;
                         if (x[i][k][j] == 0) {
                             x[i][k][j] = y[3][i][j];
                             flag = true;
                         }
                         if (x[i][k][j] == y[3][i][j]) {
                             break;
                         } else {
                             x[i][k][j] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
                 
                 
                 if (y[4][i][j] != 0) {
                     for (int k = 0; k < N; ++k) {
                         if (x[k][j][N - 1 - i] == -1) continue;
                         if (x[k][j][N - 1 - i] == 0) {
                             x[k][j][N - 1 - i] = y[4][i][j];
                             flag = true;
                         }
                         if (x[k][j][N - 1 - i] == y[4][i][j]) {
                             break;
                         } else {
                             x[k][j][N - 1 - i] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
                 
                 if (y[5][i][j] != 0) {
                     for (int k = N - 1; k >= 0; --k) {
                         if (x[k][j][i] == -1) continue;
                         if (x[k][j][i] == 0) {
                             x[k][j][i] = y[5][i][j];
                             flag = true;
                         }
                         if (x[k][j][i] == y[5][i][j]) {
                             break;
                         } else {
                             x[k][j][i] = -1;
                             flag = true;
                             continue;
                         }
                     }
                 }
             }
        }
        
        int ans = 0;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j)
          for (int k = 0; k < N; ++k)
           if (x[i][j][k] != -1) ++ans;
        
        cout << "Maximum weight: " << ans << " gram(s)" << endl;
    }
    return 0;
}
