#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const int INF = 1000000000;

class node {
public:
    int v, f, couple;
    double w;
    node() { v = 0; w = 0; f = 0; }
    node(int V, double W, int F, int CC) {v = V; w = W; f = F; couple = CC;};
};


int n, m, flow;
double cost;
int fa[MAXN], ff[MAXN];
vector<node> x[MAXN];
int X[MAXN], Y[MAXN];
double Z[MAXN][MAXN];


// s, t, capacity, cost
int newnode(int a, int b, int c, double d) {
    node p(b, d, c, x[b].size());
    node q(a, -d, 0, x[a].size());
    x[a].push_back(p);
    x[b].push_back(q);
    return 0;
}

double SPFA(int s, int t) {
    vector<double> d(n + 1, 1e20);
    vector<bool> z(n + 1, false);
    d[s] = 0;
    queue<int> que;
    que.push(s);
    z[s] = true;
    while (!que.empty()) {
        int i = que.front();
        que.pop();
        for (vector<node>::iterator p = x[i].begin(); p != x[i].end(); ++p) {
            if (p->f > 0 && d[p->v] > d[i] + p->w + 1e-10) {
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

int Min_Cost(int s, int t) {
    while (SPFA(s,t) < 1e20) {
        int i = t;
        int now = INF;
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



int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        int s = N + M + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) {
            x[i].clear();
            fa[i] = ff[i] = 0;
        }
        flow = cost = 0;
        n = t;
        
        for (int i = 1; i <= N; ++i) {
            cin >> X[i];
            newnode(s, i, X[i], 0);
        }
        for (int i = 1; i <= M; ++i) {
            cin >> Y[i];
            newnode(N + i, t, Y[i], 0);
        }
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) {
             cin >> Z[i][j];
             if (Z[i][j] != -1) newnode(i, N + j, INF, Z[i][j]);
         }
        ++times;
        cout << "Problem " << times << ": ";
        Min_Cost(s, t);
        printf("%.2lf ", cost);
        
        for (int i = 1; i <= t; ++i) {
            x[i].clear();
            fa[i] = ff[i] = 0;
        }
        flow = cost = 0;
        
        for (int i = 1; i <= N; ++i) newnode(s, i, X[i], 0);
        for (int i = 1; i <= M; ++i) newnode(N + i, t, Y[i], 0);
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) 
          if (Z[i][j] != -1) newnode(i, N + j, INF, -Z[i][j]);
        Min_Cost(s, t);
        printf("to %.2lf\n", -cost);
    }
    return 0;
}
