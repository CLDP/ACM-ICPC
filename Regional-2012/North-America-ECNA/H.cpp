#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 61;
const int INF = 1000000000;

int n, m, e;
int flow, cost;
bool x[MAXN], y[MAXN];
int lx[MAXN], ly[MAXN], l[MAXN];
int z[MAXN][MAXN];


bool find(int v) {
    int k;
    x[v] = true;
    for (int i = 1; i <= m; ++i)
     if (!y[i] && lx[v]+ly[i] == z[v][i]) {
         y[i] = true;
         k = l[i];
         l[i] = v;
         if (k == 0 || find(k)) return 1;
         l[i] = k;
     }
    return 0;
}


int match() {
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(l,0,sizeof(l));
    for (int i = 1; i <= n; ++i) 
     for (int j = 1; j <= m; ++j)
      if (z[i][j] > lx[i]) lx[i] = z[i][j];
      
    for (int k = 1; k <= n; ++k) while (1) {
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        
        if (find(k)) break;
        int d = INF;
        for (int i = 1; i <= n; ++i) if (x[i])
         for (int j = 1; j <= m; ++j) if (!y[j])
          if (d > lx[i]+ly[j]-z[i][j]) d = lx[i]+ly[j]-z[i][j];
        
        for (int i = 1; i <= n; ++i)
         if (x[i]) lx[i] -= d;
        
        for (int j = 1; j <= m; ++j) 
         if (y[j]) ly[j] += d;
    }
    
    return 0;
}

int X[MAXN][MAXN], Y[MAXN][MAXN];
int A1[MAXN], A2[MAXN];

int main() {
    int N, T = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) cin >> X[i][j];
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) cin >> Y[i][j];

        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) z[i][j] = -X[i][j];

        n = m = N;
        match();

        for (int i = 1; i <= N; ++i) A1[l[i]] = i;

        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) {
             z[i][j] = -(max(X[i][A1[i]], X[l[j]][j]) + Y[i][j]);
         }

        match();

        for (int i = 1; i <= N; ++i) A2[l[i]] = i;

        ++T;
        cout << "Case " << T << ":" << endl;

        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            cout << "Worker " << i << ": " << A1[i] << " " << A2[i] << " " << -z[i][A2[i]] << endl;
            ans -= z[i][A2[i]];
        }
        for (int i = 1; i <= N; ++i) ans -= X[i][A1[i]] + Y[i][A2[i]];

        cout << "Total idle time: " << ans << endl;
    }

    return 0;
}
