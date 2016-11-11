#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int x[55][55];
int f[110][55], y[110];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        for (int i = 1; i <= M; ++i)
         for (int j = 1; j <= M; ++j) cin >> x[i][j];
         
        for (int i = 1; i <= N; ++i) cin >> y[i];
        
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) f[i][j] = -INF;
         
        for (int i = 1; i <= M; ++i) {
            if (y[1] != -1 && y[1] != i) continue;
            f[1][i] = 0;
        }
        
        for (int i = 2; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (y[i] != -1 && y[i] != j) continue;
                f[i][j] = 0;
                for (int k = 1; k <= M; ++k) f[i][j] = max(f[i - 1][k] + x[k][j], f[i][j]);
            } 
        }
        
        int ans = 0;
        
        for (int i = 1; i <= M; ++i) ans = max(ans, f[N][i]);
        cout << ans << endl;
    }
    return 0;
}
