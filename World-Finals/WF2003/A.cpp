#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int MY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct line {
    int a, b, c;
    line() {}
    line(int _a, int _b, int _c) : a(min(_a, _b)), b(max(_a, _b)), c(_c) {}
    bool operator < (line const &B) const {
        if (c != B.c) return c < B.c;
        if (a != B.a) return a < B.a;
        return b < B.b;
    }
};

int x[110][110];
int d[5000], f[5000];


int dfs(int a, int b, int T) {
    x[a][b] = T;
    for (int i = 0; i < 8; ++i) 
     if (x[a + MX[i]][b + MY[i]] == 0) dfs(a + MX[i], b + MY[i], T);
    return 0;
}

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] = d[a] + d[b];
    d[b] = d[a];
    return 0;
}

int main() {
    int N, M, times = 0;
    bool first = true;
    while (cin >> N >> M) {
        if (N == 0) break;
        if (!first) cout << endl;
        first = false;
        for (int i = 0; i <= N + 1; ++i)
         for (int j = 0; j <= M + 1; ++j) x[i][j] = -1;
        
        for (int i = 1; i <= N; ++i) {
            string P;
            cin >> P;
            for (int j = 1; j <= M; ++j) 
             if (P[j - 1] == '#') x[i][j] = 0;
        }
        int T = 0;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j)
          if (x[i][j] == 0) dfs(i, j, ++T);
          
        set<line> S;
        for (int i = 1; i <= N + 1; ++i) {
            int curr = -1, prev = -1, len = 0;
            for (int j = 1; j <= M; ++j) {
                curr = max(x[i - 1][j], x[i][j]);
                if (curr == -1) {
                    ++len;
                    continue;
                }
                if (prev != -1 && curr != -1 && curr != prev) {
                    S.insert(line(prev, curr, len));
                }
                len = 0;
                prev = curr;
            }
        }
        
        for (int j = 1; j <= M + 1; ++j) {
            int curr = -1, prev = -1, len = 0;
            for (int i = 1; i <= N; ++i) {
                curr = max(x[i][j - 1], x[i][j]);
                if (curr == -1) {
                    ++len;
                    continue;
                }
                if (prev != -1 && curr != -1 && curr != prev) {
                    S.insert(line(prev, curr, len));
                }
                len = 0;
                prev = curr;
            }
        }
        
        vector<line> X;
        for (set<line>::iterator iter = S.begin(); iter != S.end(); ++iter) X.push_back(*iter);
        
        for (int i = 1; i <= T; ++i) {
            d[i] = 1;
            f[i] = i;
        }
        
        int ans = 0, cnt = 0;
        for (int i = 0; i < X.size(); ++i) {
            if (find(X[i].a) == find(X[i].b)) continue;
            Union(X[i].a, X[i].b);
            ++cnt;
            ans += X[i].c;
            if (cnt == T - 1) break;
        }
        
        cout << "City " << ++times << endl;
        if (T <= 1) {
            cout << "No bridges are needed." << endl;
            continue;
        }
        if (cnt == 0) {
            cout << "No bridges are possible." << endl;
            cout << T << " disconnected groups" << endl;
            continue;
        }
        cout << cnt << " bridge";
        if (cnt > 1) cout << "s";
        cout << " of total length " << ans << endl;
        if (cnt != T - 1) cout << T - cnt << " disconnected groups" << endl;
    }
    return 0;
}
