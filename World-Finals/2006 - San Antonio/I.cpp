#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 60;
const int INF = 1000000000;

int x[MAXN][MAXN];

int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) {
             if (i == j) x[i][j] = 0; else x[i][j] = INF;
         }
        map<string, int> C;
        string P, Q;
        int nn = 0;
        for (int i = 0; i < M; ++i) {
            cin >> P >> Q;
            int a, b;
            if (C.find(P) == C.end()) C[P] = ++nn;
            if (C.find(Q) == C.end()) C[Q] = ++nn;
            a = C[P];
            b = C[Q];
            x[a][b] = x[b][a] = 1;
        }
        for (int k = 1; k <= N; ++k)
         for (int i = 1; i <= N; ++i)
          for (int j = 1; j <= N; ++j) 
           if (x[i][k] + x[k][j] < x[i][j]) x[i][j] = x[i][k] + x[k][j];
        
        int ans = 0;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) ans = max(ans, x[i][j]);
        
        ++times;
        cout << "Network " << times << ": ";
        if (ans == INF) cout << "DISCONNECTED"; else cout << ans;
        cout << endl << endl;
    }
    return 0;
}
