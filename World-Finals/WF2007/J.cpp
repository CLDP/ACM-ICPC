#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 55;
const int INF = 1000000000;

int cap[MAXN][MAXN], flow[MAXN][MAXN];
int N;
bool vis[MAXN];
int M[MAXN];

bool dfs(int x) {
    if (x == 0) return true;
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = 0; i <= N; ++i)
     if (cap[x][i] > flow[x][i] && dfs(i)) {
         ++flow[x][i];
         --flow[i][x];
         return true;
     }
    return false;
}

int maxflow(int s) {
    int ans = 0;
    memset(flow, 0, sizeof(flow));
    memset(vis, 0, sizeof(vis));
    while (dfs(s)) {
        memset(vis, 0, sizeof(vis));
        ++ans;
    }
    return ans;
}


int main() {
    int T, times = 0;
    while (cin >> N >> T) {
        if (N == 0) break;
        memset(cap, 0, sizeof(cap));
        
        for (int i = 0; i < T; ++i) {
            int a, b;
            cin >> a >> b;
            ++cap[a][b];
            ++cap[b][a];
        }
        for (int i = 1; i <= N; ++i) M[i] = maxflow(i);
        
        vector<bool> Z(N + 1, false);
        for (int i = 1; i <= N; ++i) {
            int B = INF;
            for (int j = 1; j <= N; ++j)
             if (!Z[j] && M[j] < B) B = M[j];
            for (int j = 1; j <= N; ++j) {
                if (B != M[j]) continue;
                Z[j] = true;
                for (int k = 0; k <= N; ++k) cap[j][k] = cap[k][j] = 0;
            }
            for (int j = 1; j <= N; ++j) 
             if (!Z[j]) M[j] = min(M[j], B + maxflow(j));
        }
        cout << "Case " << ++times << ": " << M[1] << endl << endl;
    }
    return 0;
}
