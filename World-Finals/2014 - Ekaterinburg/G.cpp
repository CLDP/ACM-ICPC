#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const int INF = 2000000000;

int N, nn;
bool cz[MAXN * 2];
int z[MAXN * 2];
int x[MAXN][MAXN];


struct TwoSAT {
    int n;
    vector<int> G[MAXN * 2];
    bool mark[MAXN * 2];
    int S[MAXN * 2], c;

    bool dfs(int x) {
        if (mark[x ^ 1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int i = 0; i < G[x].size(); ++i) 
            if (!dfs(G[x][i])) return false;
        return true;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; ++i) G[i].clear();
        memset(mark, 0, sizeof(mark));
    }

    // xv = 1 if x, 0 if ~x
    void add_clause(int x, int xv, int y, int yv) {
        x = x * 2 + xv;
        y = y * 2 + yv;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (mark[i] || mark[i + 1]) continue;
            c = 0;
            if (!dfs(i)) {
                while (c > 0) mark[S[--c]] = false;
                if (!dfs(i + 1)) return false;
            }
        }
        return true;
    }
};

TwoSAT ts;


bool check(const int &D1, const int &D2) {
    ts.init(N);
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (x[i][j] > D2) {
                ts.add_clause(i, 1, j, 1);
                ts.add_clause(i, 0, j, 0);
            } else
            if (x[i][j] > D1) {
                ts.add_clause(i, 0, j, 0);
            }
        }
    }
    return ts.solve();
}

int MST(vector<int> &T) {
    vector<int> C(N, 0);
    for (int i = 0; i < N; ++i) {
        z[i] = 0;
        cz[i] = false;
    }
    z[0] = INF;
    C[0] = 1;
    for (int i = 0; i < N; ++i) {
        int a = 0, b = -1;
        for (int j = 0; j < N; ++j) {
            if (cz[j]) continue;
            if (z[j] > b) {
                b = z[j];
                a = j;
            }
        }
        cz[a] = true;
        T.push_back(b);
        for (int j = 0; j < N; ++j) {
            if (z[j] < x[a][j]) {
                z[j] = x[a][j];
                C[j] = -C[a];
            }
        }
    }
    T[0] = 0;
    for (int i = 0; i < N; ++i)
     for (int j = i + 1; j < N; ++j)
      if (C[i] == C[j]) T[0] = max(T[0], x[i][j]);
    return 0;
}


int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) 
     for (int j = i + 1; j < N; ++j) {
         cin >> x[i][j];
         x[j][i] = x[i][j];
     }
     
    int ans = INF;
    vector<int> T;
    MST(T);
    for (int i = 0; i < N; ++i) {
        int D1 = 0, D2 = T[i];
        if (check(D1, D2)) {
            ans = min(ans, D2); 
            continue;
        }
        D1 = D2;
        if (!check(D1, D2)) continue;
        
        int L = 0, R = D2;
        
        while (L + 1 < R) {
            D1 = (L + R) / 2;
            if (check(D1, D2))
                R = D1;
            else
                L = D1;
        }
        ans = min(ans, R + D2);
    }
    
    cout << ans << endl;
    
    return 0;
}
