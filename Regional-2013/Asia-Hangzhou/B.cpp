#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};
const int INF = 1000000000;

struct node {
    int x, y, s;
    node() {};
    node(int _x, int _y, int _s) : x(_x), y(_y), s(_s) {}
};

int z[110][110];
int d[110][110][16];
bool cz[110][110][16];


int main() {
    int N, M, T;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        int sx, sy;
        for (int i = 0; i < N; ++i) {
            string P;
            cin >> P;
            for (int j = 0; j < M; ++j) {
                if (P[j] == '#') {
                    z[i][j] = -1;
                } else {
                    z[i][j] = 0;
                    if (P[j] == '@') sx = i, sy = j;
                }
            }
        }
        cin >> T;
        bool badluck = false;
        
        int same = 0;
        for (int i = 0; i < T; ++i) {
            int a, b;
            cin >> a >> b;
            if (a < 1 || a > N || b < 1 || b > M) {
                badluck = true;
                continue;
            }
            if (z[a - 1][b - 1] == -1) {
                badluck = true;
                continue;
            }
            if (z[a - 1][b - 1] > 0) ++same; else z[a - 1][b - 1] = i + 1 - same;
        }
        
        if (badluck) {
            cout << -1 << endl;
            continue;
        }
        
        T -= same;

        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j)
          for (int k = 0; k < 16; ++k) {
              d[i][j][k] = INF;
              cz[i][j][k] = false;
          }
        
        queue<node> que;
        if (z[sx][sy] == 0) {
            que.push(node(sx, sy, 0));
            d[sx][sy][0] = 0;
            cz[sx][sy][0] = true;
        } else {
            que.push(node(sx, sy, 1 << (z[sx][sy] - 1)));
            d[sx][sy][1 << (z[sx][sy] - 1)] = 0;
            cz[sx][sy][1 << (z[sx][sy] - 1)] = true;
        }
        
        while (!que.empty()) {
            node P = que.front();
            que.pop();
            for (int k = 0; k < 4; ++k) {
                int a = P.x + MX[k], b = P.y + MY[k];
                if (a < 0 || a >= N || b < 0 || b >= M) continue;
                if (z[a][b] == -1) continue;
                int c = P.s;
                if (z[a][b] > 0) c |= (1 << (z[a][b] - 1));
                if (d[a][b][c] > d[P.x][P.y][P.s] + 1) {
                    d[a][b][c] = d[P.x][P.y][P.s] + 1;
                    if (!cz[a][b][c]) {
                        cz[a][b][c] = true;
                        que.push(node(a, b, c));
                    }
                }
            }
        }
        
        int ans = INF, S = (1 << T) - 1;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             ans = min(ans, d[i][j][S]);
         }
        
        if (ans == INF) ans = -1;
        cout << ans << endl;
        
    }
    return 0;
}
