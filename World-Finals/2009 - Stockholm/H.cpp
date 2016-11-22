#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 510;

struct node {
    int n, x[4], y[4];
};

int N, M;
vector<int> x[MAXN], y[MAXN];
node Z[MAXN];
int z[MAXN];
bool ans[MAXN][2];

bool dfs(int a) {
    bool flag = true;
    vector<int> T;
    queue<int> que;
    que.push(a);
    while (!que.empty()) {
        a = que.front();
        que.pop();
        T.push_back(a);
        if (z[a] == 1) {
            for (int j = 0; j < y[a].size(); ++j) {
                int b = y[a][j];
                for (int k = 0; k < Z[b].n; ++k) {
                    if (Z[b].x[k] == a) continue;
                    int c = Z[b].x[k];
                    if (z[c] != 0) {
                        if (z[c] != Z[b].y[k]) flag = false;
                        continue;
                    } else {
                        z[c] = Z[b].y[k];
                        que.push(c);
                    }
                }
                if (!flag) break;
            }
        } else {
            for (int j = 0; j < x[a].size(); ++j) {
                int b = x[a][j];
                for (int k = 0; k < Z[b].n; ++k) {
                    if (Z[b].x[k] == a) continue;
                    int c = Z[b].x[k];
                    if (z[c] != 0) {
                        if (z[c] != Z[b].y[k]) flag = false;
                        continue;
                    } else {
                        z[c] = Z[b].y[k];
                        que.push(c);
                    }
                }
                if (!flag) break;
            }
        }
    }
    for (int j = 0; j < T.size(); ++j) z[T[j]] = 0;
    return flag;
}


int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) x[i].clear(), y[i].clear();
        memset(z, 0, sizeof(z));
        memset(ans, 0, sizeof(ans));
        
        bool flag = true;
        for (int i = 0; i < M; ++i) {
            cin >> Z[i].n;
            for (int j = 0; j < Z[i].n; ++j) {
                string p;
                cin >> Z[i].x[j] >> p;
                if (p == "y") {
                    Z[i].y[j] = 1; 
                    x[Z[i].x[j]].push_back(i);
                } else {
                    Z[i].y[j] = -1;
                    y[Z[i].x[j]].push_back(i);
                }
            }
            if (Z[i].n < 3) {
                for (int j = 0; j < Z[i].n; ++j) {
                    if (z[Z[i].x[j]] != 0 && z[Z[i].x[j]] != Z[i].y[j]) flag = false;
                    z[Z[i].x[j]] = Z[i].y[j];
                }
            }
        }
        if (!flag) {
            cout << "Case " << ++times << ": impossible" << endl;
            continue;
        }
        
        for (int i = 1; i <= N; ++i) {
            if (z[i] != 0) {
                int temp = z[i];
                if (dfs(i)) {
                    z[i] = temp;
                    if (temp == 1) ans[i][1] = true; else ans[i][0] = true;
                }
                continue;
            }
            z[i] = 1;
            if (dfs(i)) ans[i][1] = true;
            z[i] = -1;
            if (dfs(i)) ans[i][0] = true;
            if (ans[i][0] + ans[i][1] == 1) {
                if (ans[i][0]) z[i] = -1; else z[i] = 1;
            }
        }
        flag = true;
        for (int i = 1; i <= N; ++i) flag &= (ans[i][0] || ans[i][1]);
        cout << "Case " << ++times << ": ";
        if (!flag) {
            cout << "impossible" << endl;
        } else {
            for (int i = 1; i <= N; ++i) {
                if (ans[i][0] && ans[i][1]) {
                    cout << "?";
                    continue;
                }
                if (ans[i][0]) cout << "n"; else cout << "y";
            }
            cout << endl;
        }
    }
    return 0;
}
