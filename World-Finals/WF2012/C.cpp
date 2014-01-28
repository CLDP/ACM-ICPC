#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int INF = 1000000000;

int N, M;
int f[1 << MAXN][MAXN], g[1 << MAXN][MAXN];
int x[MAXN][MAXN];


int main() {
    int times = 0;
    while (cin >> N >> M) {
        ++times;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j)
          if (i != j) x[i][j] = INF;
          
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            x[a][b] = x[b][a] = c;
        }
        
        for (int k = 0; k < N; ++k)
         for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j) 
           if (x[i][k] + x[k][j] < x[i][j]) x[i][j] = x[i][k] + x[k][j];
           
        for (int i = 1; i < N - 1; ++i) {
            f[1 << i][i] = x[0][i];    // Go from 0, end at i
            g[1 << i][i] = x[N-1][i];  // Go from N - 1, end at i
        }
        
        int H = (N - 2) / 2;
        for (int k = 1; k <= H; ++k) {
            vector<int> S(N - k, 0);
            for (int i = 0; i < k; ++i) S.push_back(1);
            
            // When S[0] != 0, it should stop
            while (S[0] == 0) {
                if (S[N - 1] != 0) {
                    next_permutation(S.begin(), S.end());
                    continue;
                }
                
                int SS = 0;
                for (int i = 1; i < N - 1; ++i) SS += S[i] * (1 << i);
                for (int i = 1; i < N - 1; ++i) {
                    if (S[i] == 0) continue;
                    for (int j = 1; j < N - 1; ++j) {
                        if (S[j] == 1) continue;
                        int NSS = SS + (1 << j);
                        if (f[NSS][j] == 0) f[NSS][j] = INF;
                        f[NSS][j] = min(f[NSS][j], f[SS][i] + x[i][j]);
                        
                        if (g[NSS][j] == 0) g[NSS][j] = INF;
                        g[NSS][j] = min(g[NSS][j], g[SS][i] + x[i][j]);
                    }
                }
                
                next_permutation(S.begin(), S.end());
            }
        }
        
        int ans = INF;
        for (int S = 0; S < (1 << N); ++S) {
            if (__builtin_popcount(S) != H) continue;
            if (S & 1) continue;
            if (S & (1 << (N - 1))) continue;
            
            int SS = 0;
            for (int i = 1; i < N - 1; ++i) SS += (1 << i) - (S & (1 << i));
            for (int i = 1; i < N - 1; ++i) {
                if ((S & (1 << i)) == 0) continue;
                for (int j = 1; j < N - 1; ++j) {
                    if ((SS & (1 << j)) == 0) continue;
                    for (int k = 1; k < N - 1; ++k) {
                        if ((S & (1 << k)) == 0) continue;
                        for (int l = 1; l < N - 1; ++l) {
                            if ((SS & (1 << l)) == 0) continue;
                            ans = min(ans, f[S][i] + x[i][j] + g[SS][j] + g[S][k] + x[k][l] + f[SS][l]);
                        }
                    }
                }
            }
        }
        
        if (N == 3) ans = (x[0][1] + x[1][2]) * 2;
        
        cout << "Case " << times << ": " << ans << endl;
        
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
    }
    return 0;
}

