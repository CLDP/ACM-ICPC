#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int e[90][90];
int f[90];

int main() {
    int TT;
    cin >> TT;
    for (int times = 1; times <= TT; ++times) {
        int N, M;
        cin >> N >> M;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) e[i][j] = 0;
            e[i][i] = -1;
        }
        
        int cc = 1;
        f[1] = 0;
        for (int i = 1; i < N - 1; ++i) {
            f[i + 1] = f[i] + cc;
            e[i][i + 1] = cc++;
            e[i + 1][i] = -1;
        }
        if (N % 3 != 1) {
            f[N] = f[N - 1] + cc;
            e[N - 1][N] = cc++;
            e[N][N - 1] = -1;
            e[N][1] = cc++;
            e[1][N] = -1;
        } else {
            e[N - 1][1] = cc++;
            e[1][N - 1] = -1;
            f[N] = f[N - 1] + cc;
            e[N - 1][N] = cc++;
            e[N][N - 1] = -1;
            e[N][1] = cc++;
            e[1][N] = -1;
        }
        while (cc <= M) {
            bool flag = false;
            for (int i = 1; i < N; ++i) {
                for (int j = i + 1; j <= N; ++j) {
                    if (e[i][j] == 0) {
                        if ((f[j] - f[i]) % 3 == cc % 3) {
                            e[i][j] = cc++;
                            e[j][i] = -1;
                            flag = true;
                            break;
                        }
                        if ((f[j] - f[i]) % 3 == 3 - (cc % 3)) {
                            e[j][i] = cc++;
                            e[i][j] = -1;
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag) break;
            }
            if (!flag) break;
        }
        if (cc <= M) {
            cout << "Case #" << times << ":" << endl << -1 << endl;
        } else {
            cout << "Case #" << times << ":" << endl;
            for (int i = 1; i <= N; ++i)
             for (int j = 1; j <= N; ++j)
              if (e[i][j] > 0) cout << i << " " << j << " " << e[i][j] << endl;
        }
    }
    
    return 0;
}
