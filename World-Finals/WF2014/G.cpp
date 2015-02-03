#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 410;
const int INF = 2000000000;

int N, nn;
bool cz[MAXN];
int f[MAXN], d[MAXN], z[MAXN];
int x[MAXN / 2][MAXN / 2];
vector<int> X[MAXN], Y[MAXN];

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a]; 
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}

int dfs1(int a) {
    cz[a] = true;
    for (int i = 0; i < X[a].size(); ++i) {
        if (!cz[X[a][i]]) dfs1(X[a][i]);
    } 
    z[nn--] = a;
    return 0;
}

int dfs2(int a, int b) {
    cz[a] = true;
    for (int i = 0; i < Y[a].size(); ++i) {
        if (!cz[Y[a][i]]) dfs2(Y[a][i], b);
    }
    Union(a, b);
    return 0;
}


bool check(const int &D1, const int &D2) {
    for (int i = 0; i < N + N; ++i) {
        X[i].clear();
        Y[i].clear();
    }
    
    for (int i = 0; i < N; ++i) 
     for (int j = i + 1; j < N; ++j) {
         if (x[i][j] > D2) {
             X[N + i].push_back(j);
             X[N + j].push_back(i);
             X[i].push_back(N + j);
             X[j].push_back(N + i);
             Y[N + i].push_back(j);
             Y[N + j].push_back(i);
             Y[i].push_back(N + j);
             Y[j].push_back(N + i);
         } else
         if (x[i][j] > D1) {
             X[i].push_back(N + j);
             X[j].push_back(N + i);
             Y[N + i].push_back(j);
             Y[N + j].push_back(i);
         }
     }
    
    nn = N + N;
    memset(cz, 0, sizeof(cz));
    for (int i = 0; i < N + N; ++i) {
        if (!cz[i]) dfs1(i);
        f[i] = i;
        d[i] = 1;
    }
    memset(cz, 0, sizeof(cz));
    for (int i = 1; i <= N + N; ++i) {
        if (!cz[z[i]]) dfs2(z[i], z[i]);
    }
    
    for (int i = 0; i < N; ++i)
     if (find(i) == find(N + i)) return false;
    
    return true;
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
