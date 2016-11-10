#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 10000000;

int V[MAXN];
int f[MAXN][MAXN], g[MAXN][MAXN];
int h[MAXN], in[MAXN];

int main() {
    int N, M;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &V[i]);
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) 
      if (i != j) f[i][j] = g[i][j] = INF;
      
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);
        f[a][b] = f[b][a] = g[b][a] = g[a][b];
    }
    
    for (int k = 1; k <= N; ++k)
     for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j) 
       if (f[i][k] + f[k][j] < f[i][j]) f[i][j] = f[i][k] + f[k][j];
    
    
    
    if (f[1][N] == INF) {
        cout << "impossible" << endl;
        return 0;
    }
    
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) {
         if (f[1][i] + g[i][j] + f[j][N] != f[1][N]) g[i][j] = INF;
         if (g[i][j] != INF && i != j) ++in[j];
     }
    
    
    queue<int> Q;
    Q.push(1);
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        h[a] += V[a];
        for (int i = 1; i <= N; ++i) {
            if (g[a][i] == INF) continue;
            if (a == i) continue;
            h[i] = max(h[i], h[a]);
            --in[i];
            if (in[i] == 0) Q.push(i);
        }
    }
    cout << f[1][N] << " " << h[N] << endl;
    
    return 0;
}
