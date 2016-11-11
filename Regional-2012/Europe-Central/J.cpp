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

const int MAXN = 100010;

int Y[MAXN], IN[MAXN];
vector<int> X[MAXN];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, a, b;
        cin >> N >> M;
        for (int i = 1; i <= N; ++i) {
            X[i].clear();
            scanf("%d", &Y[i]);
            --Y[i];
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &a, &b);
            X[a].push_back(b);
        }
        
        int ans = N;
        
        for (int start = 0; start < 2; ++start) {
            for (int i = 1; i <= N; ++i) {
                for (int j = 0; j < X[i].size(); ++j) ++IN[X[i][j]];
            }
            vector<int> P[2];
            for (int i = 1; i <= N; ++i) {
                if (IN[i] != 0) continue;
                if (Y[i] == 0) P[0].push_back(i); else P[1].push_back(i);
            }
            bool curr = start;
            int NN = N, temp = -1;
            while (NN > 0) {
                ++temp;
                for (int i = 0; i < P[curr].size(); ++i) {
                    int a = P[curr][i];
                    for (int j = 0; j < X[a].size(); ++j) {
                        --IN[X[a][j]];
                        if (IN[X[a][j]] == 0) P[Y[X[a][j]]].push_back(X[a][j]);
                    }
                    --NN;
                }
                P[curr].clear();
                curr = !curr;
            }
            ans = min(ans, temp);
            
        }
        cout << ans << endl;
    }
    return 0;
}
