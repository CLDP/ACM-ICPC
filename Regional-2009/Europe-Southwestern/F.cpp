#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const long long INF = 1000000000000;

vector<pair<int, int> > x[910];
int z[31][31];
long long d[910];
int cnt[910];
bool cz[910];

int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N * M; ++i) x[i].clear();
        memset(z, 0, sizeof(z));
        int T;
        cin >> T;
        for (int i = 0; i < T; ++i) {
            int a, b;
            cin >> a >> b;
            z[a][b] = 1;
        }
        cin >> T;
        for (int i = 0; i < T; ++i) {
            int a, b, c, d, t;
            cin >> a >> b >> c >> d >> t;
            z[a][b] = 2;
            x[a * M + b + 1].push_back(make_pair(c * M + d + 1, t));
        }
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             if (z[i][j] != 0) continue;
             if (i == N - 1 && j == M - 1) continue;
             if (i > 0 && z[i - 1][j] != 1) x[i * M + j + 1].push_back(make_pair((i - 1) * M + j + 1, 1));
             if (i < N - 1 && z[i + 1][j] != 1) x[i * M + j + 1].push_back(make_pair((i + 1) * M + j + 1, 1));
             if (j > 0 && z[i][j - 1] != 1) x[i * M + j + 1].push_back(make_pair(i * M + j, 1));
             if (j < M - 1 && z[i][j + 1] != 1) x[i * M + j + 1].push_back(make_pair(i * M + j + 2, 1));
         }
        
        for (int i = 1; i <= N * M; ++i) {
            d[i] = INF;
            cz[i] = false;
            cnt[i] = 0;
        }
        
        queue<int> que;
        que.push(1);
        d[1] = 0;
        cz[1] = true;
        cnt[1] = 1;
        bool flag = false;
        while (!que.empty()) {
            int a = que.front();
            que.pop();
            cz[a] = false;
            
            if (cnt[a] == 2 * N * M + 1) {
                flag = true;
                break;
            }
            for (int i = 0; i < x[a].size(); ++i) {
                if (d[x[a][i].first] > d[a] + x[a][i].second) {
                    d[x[a][i].first] = d[a] + x[a][i].second;
                    if (!cz[x[a][i].first]) {
                        cz[x[a][i].first] = true;
                        que.push(x[a][i].first);
                        ++cnt[x[a][i].first];
                    }
                }
            }
            
        }
        
        if (flag) {
            cout << "Never" << endl;
            continue;
        }
        if (d[N * M] == INF) {
            cout << "Impossible" << endl;
        } else {
            cout << d[N * M] << endl;
        }
        
    }
    return 0;
}
