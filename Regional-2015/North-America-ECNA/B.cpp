#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int X[110][2], Y[110][2];

int main() {
    int R, C, N, M;
    cin >> R >> C >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i][0] >> X[i][1];
    for (int i = 0; i < M; ++i) cin >> Y[i][0] >> Y[i][1];
    if (N == 0) {
        cout << 0 << endl;
        return 0;
    }
    int ans = N + M;
    for (int u = 0; u < N; ++u) {
        for (int b = 0; b < N; ++b) {
            if (X[u][0] > X[b][0]) continue;
            if (X[b][0] + 7 >= R) continue;
            
            int U = X[u][0] + 7, B = X[b][0] + 7;

            int cnt = N;
            for (int i = 0; i < N; ++i) {
                if (U <= X[i][0] + 7 && X[i][0] + 7 <= B) --cnt;
            }
            if (cnt > ans) continue;

            for (int l = 0; l < N; ++l) {
                for (int r = 0; r < N; ++r) {
                    if (X[l][1] > X[r][1]) continue;
                    if (X[r][1] + 4 >= C) continue;
                    int L = X[l][1] + 4, R = X[r][1] + 4;
                    int cnt = N;
                    for (int i = 0; i < N; ++i) {
                        if (U <= X[i][0] + 7 && X[i][0] + 7 <= B 
                         && L <= X[i][1] + 4 && X[i][1] + 4 <= R) --cnt;
                    }
                    if (cnt > ans) continue;
                    for (int i = 0; i < M; ++i) {
                        if (U <= Y[i][0] + 7 && Y[i][0] + 7 <= B 
                         && L <= Y[i][1] + 4 && Y[i][1] + 4 <= R) ++cnt;
                    }
                    ans = min(ans, cnt);
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
