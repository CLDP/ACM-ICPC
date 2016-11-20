#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

const long long MAXN = 10010;
const long long INF = 1000000000;

class node {
public:
    long long v, w, f, couple;
    node() {v = w = f = 0;}
    node(long long V, long long W, long long F, long long CC) {
        v = V;
        w = W;
        f = F;
        couple = CC;
    }
};

long long n, m, flow, cost;
long long fa[MAXN], ff[MAXN];
vector<node> x[MAXN];

long long newnode(long long a, long long b, long long c, long long d) {
    node p(b, d, c, x[b].size());
    node q(a, -d, 0, x[a].size());
    x[a].push_back(p);
    x[b].push_back(q);
    return 0;
}

long long SPFA(long long s, long long t) {
    vector<long long> d(n + 1, INF);
    vector<bool> z(n + 1, false);
    d[s] = 0;
    queue<long long> que;
    que.push(s);
    z[s] = true;
    while (!que.empty()) {
        long long i = que.front();
        que.pop();
        for (vector<node>::iterator p = x[i].begin(); p != x[i].end(); ++p) {
            if (p->f > 0 && d[p->v] > d[i] + p->w) {
                d[p->v] = d[i] + p->w;
                fa[p->v] = i;
                ff[p->v] = p - x[i].begin();
                if (!z[p->v]) {
                    z[p->v] = true;
                    que.push(p->v);
                }
            }
            
        }
        z[i] = false;
    }
    return d[t];
}

long long Min_Cost(long long s, long long t) {
    while (SPFA(s, t) < INF) {
        long long i = t, now = INF;
        while (i != s) {
            node &p = x[fa[i]][ff[i]];
            i = fa[i];
            if (p.f < now) now = p.f;
        }
        flow += now;
        
        i = t;
        while (i != s) {
            x[fa[i]][ff[i]].f -= now;
            cost += now * x[fa[i]][ff[i]].w;
            x[i][x[fa[i]][ff[i]].couple].f += now;
            i = fa[i];
        }
    }
    return 0;
}


long long Y[110][110];

int main() {
    long long N, T;
    cin >> N >> T;
    for (long long i = 0; i < N; ++i) 
     for (long long j = i + 1; j <= N; ++j) cin >> Y[i][j];
    
    const long long FINF = -1000000000;
    
    long long ans = INF;
    for (int TT = 1; TT <= T; ++TT) {
        for (int i = 1; i <= N + N + 10; ++i) {
            x[i].clear();
            fa[i] = ff[i] = 0;
        }
        flow = cost = n = m = 0;
        
        long long s = N + N + 1, t = s + 1;
        for (long long i = 1; i <= N; ++i) {
            newnode(i, i + N, 1, FINF);
            newnode(s, i, 1, Y[0][i]);
            newnode(i + N, t, 1, 0);
            for (long long j = i + 1; j <= N; ++j) newnode(i + N, j, 1, Y[i][j]);
        }
        newnode(t + 1, s, TT, 0);
        s = t + 1;
        n = s;
        Min_Cost(s, t);
        ans = min(ans, cost - FINF * N);
    }
    cout << ans << endl;
    return 0;
}
