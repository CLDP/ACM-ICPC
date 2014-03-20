#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 30;
const int INF = 1000000000;

struct ANS {
    int cost;
    vector<int> C;
};


int N, T, M, R;
bool z[MAXN];
vector<pair<int, int> > X[MAXN];
vector<int> S;
ANS ans;

int dfs(int a) {
    if (a == N + 1) {
        bool cz[MAXN];
        int d[MAXN];
        int total = 0;
        for (int i = 1; i <= N; ++i) {
            cz[i] = false;
            d[i] = INF;
            total += z[i];
        }
        int temp = 0;
        d[T] = 0;
        for (int i = 0; i < total; ++i) {
            int a = -1, b = INF;
            for (int j = 1; j <= N; ++j) {
                if (cz[j] || !z[j]) continue;
                if (d[j] < b) {
                    a = j;
                    b = d[j];
                }
            }
            temp += b;
            cz[a] = true;
            for (int j = 0; j < X[a].size(); ++j)
                d[X[a][j].first] = min(d[X[a][j].first], X[a][j].second);
        }
        vector<int> CC;
        for (int i = 1; i <= N; ++i) {
            if (z[i] && !cz[i]) return 0;
            if (!z[i]) continue;
            CC.push_back(i);
        }
        
        if (temp > ans.cost) return 0;
        
        if (temp < ans.cost) {
            ans.cost = temp;
            ans.C = CC;
            return 0;
        }
        if (total < ans.C.size()) {
            ans.C = CC;
            return 0;
        }
        if (CC < ans.C) ans.C = CC;
        return 0;
    }
    if (z[a]) {
        dfs(a + 1);
    } else {
        dfs(a + 1);
        z[a] = true;
        dfs(a + 1);
        z[a] = false;
    }
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N) {
        if (N == -1) break;
        
        for (int i = 1; i <= N; ++i) X[i].clear();
        cin >> T >> M;
        z[T] = true;
        int a, b, c;
        for (int i = 0; i < M; ++i) {
            cin >> a >> b >> c;
            X[a].push_back(make_pair(b, c));
            X[b].push_back(make_pair(a, c));
        }
        cin >> R;
        memset(z, 0, sizeof(z));
        z[T] = true;
        S.clear();
        for (int i = 0; i < R; ++i) {
            cin >> a;
            S.push_back(a);
            z[a] = true;
        }
        
        ans.cost = INF;
        dfs(1);
        
        cout << "Case " << ++times << ": distance = " << ans.cost << endl;
        
        vector<int> x[MAXN];
        bool cz[MAXN];
        int d[MAXN], f[MAXN];
        memset(z, 0, sizeof(z));
        for (int i = 0; i < ans.C.size(); ++i) z[ans.C[i]] = true;
        for (int i = 1; i <= N; ++i) {
            cz[i] = false;
            d[i] = INF;
        }
        d[T] = 0;
        for (int i = 0; i < ans.C.size(); ++i) {
            int a = -1, b = INF;
            for (int j = 1; j <= N; ++j) {
                if (cz[j] || !z[j]) continue;
                if (d[j] < b) {
                    a = j;
                    b = d[j];
                }
            }
            cz[a] = true;
            if (a != T) {
                x[a].push_back(f[a]);
                x[f[a]].push_back(a);
            }
            for (int j = 0; j < X[a].size(); ++j) {
                if (d[X[a][j].first] > X[a][j].second) {
                    d[X[a][j].first] = X[a][j].second;
                    f[X[a][j].first] = a;
                }
            }
        }
        memset(z, 0, sizeof(z));
        queue<int> que;
        que.push(T);
        z[T] = true;
        while (!que.empty()) {
            a = que.front();
            que.pop();
            for (int i = 0; i < x[a].size(); ++i) 
             if (!z[x[a][i]]) {
                 z[x[a][i]] = true;
                 que.push(x[a][i]);
                 f[x[a][i]] = a;
             }
        }
        
        for (int i = 0; i < S.size(); ++i) {
            cout << "   ";
            while (S[i] != T) {
                cout << S[i] << "-";
                S[i] = f[S[i]];   
            }
            cout << T << endl;
        }
        
        cout << endl;
    }
    return 0;
}
