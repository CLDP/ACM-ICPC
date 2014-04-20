#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;

struct node {
    int a, b, c;
    node() {}
    node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};


vector<pair<int, int> > x[MAXN][MAXN], y[MAXN][MAXN];
int D[MAXN][MAXN][5];
bool z[MAXN][MAXN][5];


int main() {
    int N, M, sx, sy, tx, ty, times = 0;
    while (cin >> N >> M >> sx >> sy >> tx >> ty) {
        if (N == 0 && M == 0) break;
        --sx, --sy, --tx, --ty;
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             x[i][j].clear();
             y[i][j].clear();
         }
         
        for (int i = 0; i < N; ++i) {
            int a;
            for (int j = 1; j < M; ++j) {
                cin >> a;
                if (a == 0) continue;
                y[i][j - 1].push_back(make_pair(1, a));
                y[i][j].push_back(make_pair(-1, a));
            }
            if (i == N - 1) break;
            for (int j = 0; j < M; ++j) {
                cin >> a;
                if (a == 0) continue;
                x[i][j].push_back(make_pair(1, a));
                x[i + 1][j].push_back(make_pair(-1, a));
            }
        }
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j)
          for (int k = 0; k < 5; ++k) {
              D[i][j][k] = INF;
              z[i][j][k] = false;
          }
        
        queue<node> que;
        D[sx][sy][4] = 0;
        z[sx][sy][4] = true;
        que.push(node(sx, sy, 4));
        
        while (!que.empty()) {
            node T = que.front();
            que.pop();
            int a = T.a, b = T.b, c = T.c;
            // k == 0 - 3    x-  y+  x+  y-
            
            if (c == 4) {
                // start from stop
                for (int i = 0; i < x[a][b].size(); ++i) {
                    int p = a + x[a][b][i].first, q = b, r = x[a][b][i].first > 0 ? 2 : 0;
                    // stop and on
                    if (D[p][q][r] > D[a][b][c] + x[a][b][i].second * 2) {
                        D[p][q][r] = D[a][b][c] + x[a][b][i].second * 2;
                        if (!z[p][q][r]) {
                            z[p][q][r] = true;
                            que.push(node(p, q, r));
                        }
                    }
                    // stop and stop
                    if (D[p][q][4] > D[a][b][c] + x[a][b][i].second * 2) {
                        D[p][q][4] = D[a][b][c] + x[a][b][i].second * 2;
                        if (!z[p][q][4]) {
                            z[p][q][4] = true;
                            que.push(node(p, q, 4));
                        }
                    }
                }
                for (int j = 0; j < y[a][b].size(); ++j) {
                    int p = a, q = b + y[a][b][j].first, r = y[a][b][j].first > 0 ? 1 : 3;
                    // stop and on
                    if (D[p][q][r] > D[a][b][c] + y[a][b][j].second * 2) {
                        D[p][q][r] = D[a][b][c] + y[a][b][j].second * 2;
                        if (!z[p][q][r]) {
                            z[p][q][r] = true;
                            que.push(node(p, q, r));
                        }
                    }
                    // stop and stop
                    if (D[p][q][4] > D[a][b][c] + y[a][b][j].second * 2) {
                        D[p][q][4] = D[a][b][c] + y[a][b][j].second * 2;
                        if (!z[p][q][4]) {
                            z[p][q][4] = true;
                            que.push(node(p, q, 4));
                        }
                    }
                }
                
                z[a][b][c] = false;
                continue;
            }
            
            // Try all direction
            for (int i = 0; i < x[a][b].size(); ++i) {
                int p = a + x[a][b][i].first, q = b, r = x[a][b][i].first > 0 ? 2 : 0;
                if (r != c) continue;
                if (D[p][q][r] > D[a][b][c] + x[a][b][i].second) {
                    D[p][q][r] = D[a][b][c] + x[a][b][i].second;
                    if (!z[p][q][r]) {
                        z[p][q][r] = true;
                        que.push(node(p, q, r));
                    }
                }
                if (D[p][q][4] > D[a][b][c] + x[a][b][i].second * 2) {
                    D[p][q][4] = D[a][b][c] + x[a][b][i].second * 2;
                    if (!z[p][q][4]) {
                        z[p][q][4] = true;
                        que.push(node(p, q, 4));
                    }
                }
            }
        
            for (int j = 0; j < y[a][b].size(); ++j) {
                int p = a, q = b + y[a][b][j].first, r = y[a][b][j].first > 0 ? 1 : 3;
                if (r != c) continue;
                if (D[p][q][r] > D[a][b][c] + y[a][b][j].second) {
                    D[p][q][r] = D[a][b][c] + y[a][b][j].second;
                    if (!z[p][q][r]) {
                        z[p][q][r] = true;
                        que.push(node(p, q, r));
                    }
                }
                if (D[p][q][4] > D[a][b][c] + y[a][b][j].second * 2) {
                    D[p][q][4] = D[a][b][c] + y[a][b][j].second * 2;
                    if (!z[p][q][4]) {
                        z[p][q][4] = true;
                        que.push(node(p, q, 4));
                    }
                }
            }
            
            z[a][b][c] = false;
        }
        cout << "Case " << ++times << ": ";
        if (D[tx][ty][4] == INF) cout << "Impossible" << endl; else cout << D[tx][ty][4] << endl;
    }
    return 0;
}
