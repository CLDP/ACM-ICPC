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

const int MAXN = 102;
const int INF = 1000000000;

struct label {
    int a, b, c, d;
    bool operator < (const label &B) const {
        if (a != B.a) return a < B.a;
        if (b != B.b) return b < B.b;
        if (c != B.c) return c < B.c;
        return d < B.d;
    }
};

struct node {
    int x[3], t;
};

label getlabel(const node &B, const vector<int> &T) {
    label P;
    P.a = T[B.x[0]];
    P.b = T[B.x[1]];
    P.c = T[B.x[2]];
    P.d = B.t;
    return P;
}

vector<node> reduce(const vector<node> &X) {
    int N = X.size();
    vector<int> G[MAXN], F[MAXN];
    vector<int> T(N, 0);
    for (int i = 0; i < N; ++i) {
        G[X[i].t].push_back(i);
        T[i] = X[i].t;
    }
    
    int M = 3;
    bool first = true;
    map<label, int> C;
    while (true) {
        int MM = 0;
        C.clear();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < G[i].size(); ++j) {
                label P = getlabel(X[G[i][j]], T);
                if (C.find(P) == C.end()) C[P] = MM++;
                int Q = C[P];
                F[Q].push_back(G[i][j]);
            }
        }
        
        vector<int> TT;
        for (int i = 0; i < N; ++i) {
            label P = getlabel(X[i], T);
            TT.push_back(C[P]);
        }
        T = TT;
        
        if (!first && M == MM) break;
        
        
        M = MM;
        first = false;
        for (int i = 0; i < M; ++i) {
            G[i] = F[i];
            F[i].clear();
        }
    }
    
    vector<node> Y;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < G[i].size(); ++j) {
            label P = getlabel(X[G[i][j]], T);
            if (C.find(P) == C.end()) continue;
            int Q = C[P];
            C.erase(P);
            node R;
            R.t = X[G[i][j]].t;
            R.x[0] = P.a;
            R.x[1] = P.b;
            R.x[2] = P.c;
            Y.push_back(R);
        }
    }
    
    return Y;
}

int MM;
node ans[50010];
map<vector<int>, int> SS;

int dfs(const int PREV, const vector<int> Z, const vector<node> &X) {
    int N = Z.size();
    SS[Z] = PREV;
    
    // this times output
    vector<int> Y[3];
    for (int i = 0; i < N; ++i) {
        Y[X[Z[i]].t].push_back(Z[i]);
    }
    
    ans[PREV].t = 0;
    for (int i = 0; i < 3; ++i) {
        if (Y[i].size() == 0) {
            ans[PREV].x[i] = PREV;
            continue;
        }
        if (Y[i].size() == N) {
            int P = (X[Z[0]].t + 1) % 3;
            vector<int> ZZ;
            for (int j = 0; j < N; ++j) ZZ.push_back(X[Z[j]].x[P]);
            ans[PREV].t = P;
            if (SS.find(ZZ) != SS.end()) {
                ans[PREV].x[i] = SS[ZZ];
            } else {
                ans[PREV].x[i] = ++MM;
                dfs(MM, ZZ, X);
            }
            continue;
        }
        
        ans[PREV].x[i] = ++MM;
        for (int j = 0; j < Y[i].size(); ++j) Y[i][j] = X[Y[i][j]].x[0];
        dfs(MM, Y[i], X);
    }
    return 0;
}

int main() {
    freopen("epic.in", "r", stdin);
    freopen("epic.out", "w", stdout);
    int N;
    cin >> N;
    vector<node> X;
    for (int i = 0; i < N; ++i) {
        char p;
        node t;
        cin >> p >> t.x[0] >> t.x[1] >> t.x[2];
        --t.x[0];
        --t.x[1]; 
        --t.x[2];
        switch (p) {
            case 'R' : t.t = 0; break;
            case 'P' : t.t = 1; break;
            case 'S' : t.t = 2; break;
        }
        X.push_back(t);
    }
    
    X = reduce(X);
    N = X.size();
    
    vector<int> Z;
    for (int i = 0; i < N; ++i) Z.push_back(i);
    MM = 1;
    dfs(MM, Z, X);
    
    cout << MM << endl;
    for (int i = 1; i <= MM; ++i) {
        switch (ans[i].t) {
            case 0 : cout << "R "; break;
            case 1 : cout << "P "; break;
            case 2 : cout << "S "; break;
        }
        for (int j = 0; j < 3; ++j) cout << ans[i].x[j] << " "; 
        cout << endl;
    }
    
    return 0;
}
