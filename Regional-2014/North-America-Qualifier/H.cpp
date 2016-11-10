#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T[3][3] = {0, 1, 2, 0, 1, 1, 2, 2, 0};

int f[210][210][3];
int x[210], y[210];

int main() {
    int N, K;
    while (cin >> N >> K) {
        if (N == 0 && K == 0) return 0;
        for (int i = 1; i <= N; ++i) cin >> x[i] >> y[i];
        memset(f, 0, sizeof(f));
        for (int k = 1; k <= K; ++k) f[0][k][0] = f[0][k][1] = f[0][k][2] = 1000000;
        
        for (int i = 1; i <= N; ++i)
         for (int j = 0; j <= K; ++j)
          for (int k = 0; k < 3; ++k) {
              f[i][j][k] = 1000000;
              if (k != 0 && j == 0) continue;
              if (k == 0) {
                  for (int l = 0; l < 3; ++l) {
                      f[i][j][k] = min(f[i][j][k], f[i - 1][j][T[k][l]]);
                  }
              } else {
                  int temp = 0;
                  if (k == 1) temp = x[i]; else temp = y[i];
                  for (int l = 0; l < 3; ++l) {
                      f[i][j][k] = min(f[i - 1][j - 1][T[k][l]] + temp, f[i][j][k]);
                  }
              }
          }
         
         int sum = 0;
         for (int i = 1; i <= N; ++i) sum += x[i] + y[i];
         cout << sum - min(f[N][K][0], min(f[N][K][1], f[N][K][2])) << endl;
    }

    return 0;
}
