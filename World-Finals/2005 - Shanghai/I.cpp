#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;

// z is the weight matrix input
int z[MAXN][MAXN], zz[MAXN][MAXN];
bool x[MAXN], y[MAXN];
int lx[MAXN], ly[MAXN];

// l is the matching result, see below for usage
int l[MAXN], ll[MAXN], flow, cost;

bool find(int v, int M) {
    int k;
    x[v] = true;
    for (int i = 1; i <= M; ++i) {
        if (!y[i] && lx[v] + ly[i] == z[v][i]) {
            y[i] = true;
            k = l[i];
            l[i] = v;
            if (k == 0 || find(k, M)) return true;
            l[i] = k;
        }
    }
    return false;
}

int match(int N, int M, int t) {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (z[i][j] > lx[i]) lx[i] = z[i][j];
        }
    }
      
    for (int k = t + 1; k <= N; ++k) while (true) {
        if (ll[k]) break;
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        
        if (find(k, M)) break;
        int d = INF;
        for (int i = 1; i <= N; ++i) if (x[i])
         for (int j = 1; j <= M; ++j) if (!y[j])
          if (d > lx[i] + ly[j] - z[i][j]) d = lx[i] + ly[j] - z[i][j];
        
        for (int i = 1; i <= N; ++i)
         if (x[i]) lx[i] -= d;
        
        for (int j = 1; j <= M; ++j) 
         if (y[j]) ly[j] += d;
    }
    
    flow = cost = 0;
    for (int i = 1; i <= M; ++i) {
        if (l[i] == 0 || z[l[i]][i] == 1) continue;
        ++flow;
        cost += z[l[i]][i] - 1;
    }
    
    return 0;
}

pair<int, int> X[MAXN];
pair<int, int> Y[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int times = 0, N, M;
    while (cin >> N) {
        if (N == 0) break;
        int total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> X[i].first >> X[i].second;
            total += X[i].first;
        }
        cin >> M;
        for (int i = 0; i < M; ++i) {
            string P;
            cin >> Y[i].first >> P;
            Y[i].second = (atoi(P.substr(0, 2).c_str()) - 14) * 60 + atoi(P.substr(3, 2).c_str());
        }
        
        memset(lx, 0, sizeof(lx));
        memset(ly, 0, sizeof(ly));
        memset(l, 0, sizeof(l));
        vector<int> S, K;
        for (int i = 0; i < N; ++i) {
            zz[i + 1][M + i + 1] = 1;
            bool flag = true;
            for (int j = 0; j < M; ++j) {
                zz[i + 1][j + 1] = 1;
                if (X[i].first <= Y[j].first && X[i].second <= Y[j].second) {
                    zz[i + 1][j + 1] = X[i].first + 1;
                    if (flag && l[j + 1] == 0) {
                        l[j + 1] = S.size() + 1;
                        S.push_back(i + 1);
                        flag = false;
                    }
                }
            }
            if (flag) K.push_back(i + 1);
        }

        for (int i = 0; i < S.size(); ++i) {
            for (int j = 1; j <= M; ++j) z[i + 1][j] = zz[S[i]][j];
        }
        for (int i = 0; i < K.size(); ++i) {
            for (int j = 1; j <= M; ++j) z[S.size() + i + 1][j] = zz[K[i]][j];
        } 
        if (N > M) {
            for (int i = 1; i <= N; ++i) {
                for (int j = M + 1; j <= N; ++j) z[i][j] = 1;
            }
        }
        match(N, max(N, M), S.size());
        cout << "Trial " << ++times << ": " << N - flow << " " << total - cost << endl << endl;
    }
    return 0;
}
