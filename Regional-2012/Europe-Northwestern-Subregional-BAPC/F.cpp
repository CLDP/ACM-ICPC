#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};


int N, M;
string X[1010];
int f[1010][1010];

bool inside(int a, int b) {
    return 0 <= a && a < N && 0 <= b && b < M && X[a][b] == '.';
}


int main() {
    int times;
    cin >> times;
    for (int tt = 0; tt < times; ++tt) {
        cin >> M >> N;
        for (int i = 0; i < N; ++i) cin >> X[i];
        vector<pair<int, int> > Q, QT;
        queue<pair<int, int> > que;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             if (X[i][j] == '*') Q.push_back(make_pair(i, j));
             if (X[i][j] == '@') {
                 que.push(make_pair(i, j));
                 X[i][j] = '.';
             }
         }
        
        memset(f, -1, sizeof(f));
        f[que.front().first][que.front().second] = 0;
        int current = -1;
        while (!que.empty()) {
            int A = que.front().first, B = que.front().second;
            que.pop();
            if (f[A][B] != current) {
                for (int i = 0; i < Q.size(); ++i) {
                    int s = Q[i].first, t = Q[i].second;
                    for (int j = 0; j < 4; ++j) {
                        if (!inside(s + MX[j], t + MY[j])) continue;
                        X[s + MX[j]][t + MY[j]] = '*';
                        QT.push_back(make_pair(s + MX[j], t + MY[j]));
                    }
                }
                Q = QT;
                QT.clear();
                ++current;
            }
            for (int i = 0; i < 4; ++i) {
                if (!inside(A + MX[i], B + MY[i])) continue;
                if (f[A + MX[i]][B + MY[i]] != -1) continue;
                f[A + MX[i]][B + MY[i]] = f[A][B] + 1;
                que.push(make_pair(A + MX[i], B + MY[i]));
            }
        }
        int ans = INF;
        for (int i = 0; i < N; ++i) {
            if (f[i][0] != -1) ans = min(ans, f[i][0]);
            if (f[i][M - 1] != -1) ans = min(ans, f[i][M - 1]);
        }
        for (int i = 0; i < M; ++i) {
            if (f[0][i] != -1) ans = min(ans, f[0][i]);
            if (f[N - 1][i] != -1) ans = min(ans, f[N - 1][i]);
        }
        if (ans == INF) cout << "IMPOSSIBLE" << endl; else cout << ans + 1 << endl;
    }
    
    return 0;
}
