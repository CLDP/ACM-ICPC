#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAXN = 2101;
const int INF = 1000000000;

class node {
public:
    int v, w, f, couple;
    node() { v = 0; w = 0; f = 0; }
    node(int V, int W, int F, int CC) {v = V; w = W; f = F; couple = CC;};
};

int n, m, flow, cost;
int fa[MAXN], ff[MAXN];
vector<node> x[MAXN];

// s, t, capacity, cost
int newnode(int a, int b, int c, int d) {
    node p(b, d, c, x[b].size());
    node q(a, -d, 0, x[a].size());
    x[a].push_back(p);
    x[b].push_back(q);
    return 0;
}

int SPFA(int s, int t) {
    vector<int> d(n + 1, INF);
    vector<bool> z(n + 1, false);
    d[s] = 0;
    queue<int> que;
    que.push(s);
    z[s] = true;
    while (!que.empty()) {
        int i = que.front();
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

int Min_Cost(int s, int t) {
    while (SPFA(s,t) < INF) {
        int i = t, now = INF;
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
    int times = 0, N, M;
    while (cin >> N) {
        if (N == 0) break;
        vector<pair<int, int> > X(N);
        int total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> X[i].first >> X[i].second;
            total += X[i].first;
        }
        cin >> M;
        vector<pair<int, int> > Y(N);
        
        for (int i = 0; i < M; ++i) {
            string P;
            cin >> Y[i].first >> P;
            Y[i].second = (atoi(P.substr(0, 2).c_str()) - 14) * 60 + atoi(P.substr(3, 2).c_str());
        }
        
        int s = N + M + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) x[i].clear();
        memset(fa, 0, sizeof(fa));
        memset(ff, 0, sizeof(ff));
        flow = cost = 0;
        n = t;
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) 
          if (X[i].second <= Y[i].second) {
              newnode(i + 1, N + j + 1, 1, -X[i].first);
          }
        
        for (int i = 1; i <= N; ++i) newnode(s, i, 1, 0);
        for (int j = 1; j <= M; ++j) newnode(N + j, t, 1, 0);
        
        Min_Cost(s, t);
        cout << "Trial " << ++times << ": " << N - flow << " " << total + cost << endl << endl;
    }
    return 0;
}

