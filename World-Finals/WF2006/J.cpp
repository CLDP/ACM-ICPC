#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;

int x[MAXN][MAXN], y[MAXN][MAXN];
bool z[MAXN][MAXN];
queue<pair<int, int> > que;


int relax(int a, int b, int fab) {
    if (fab < y[a][b]) {
        y[a][b] = fab;
        if (!z[a][b]) {
            z[a][b] = true;
            que.push(make_pair(a, b));
        }
    }
    return 0;
}


int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) x[i][j] = INF;
        
        int a, b;
        for (int i = 0; i < M; ++i) {
            cin >> a >> b;
            x[a][b] = 1;
        }
        
        for (int k = 1; k <= N; ++k)
         for (int i = 1; i <= N; ++i)
          for (int j = 1; j <= N; ++j) 
           if (x[i][k] + x[k][j] < x[i][j]) x[i][j] = x[i][k] + x[k][j];
        
        
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) y[i][j] = INF;
        
        y[1][1] = 1;
        z[1][1] = true;
        que.push(make_pair(1, 1));
        
        while (!que.empty()) {
            int a = que.front().first, b = que.front().second;
            que.pop();
            
            relax(b, a, y[a][b] + x[a][b] - 1);
            
            for (int i = 1; i <= N; ++i) {
                relax(i, b, y[a][b] + x[a][i] - (i == b));
                relax(a, i, y[a][b] + x[i][b] - (i == a));
            }
            
            z[a][b] = false;
        }
        
        ++times;
        cout << "Network " << times << endl;
        if (y[2][2] == INF) cout << "IMPOSSIBLE" << endl; else cout << "Minimum number of nodes = " << y[2][2] << endl;
        cout << endl;
        
    }
    return 0;
}
