const int MAXN = 1100;
const int INF = 1000000000;

class node {
public:
    int v, w, f, couple;
    node() { v = 0; w = 0; f = 0; }
    node(int V, int W, int F, int CC) {v = V; w = W; f = F; couple = CC;};
};

int flow, cost;
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

int SPFA(int s, int t, int n) {
    vector<int> d(n + 1, INF);
    vector<bool> z(n + 1, false);
    d[s] = 0;
    queue<int> Q;
    Q.push(s);
    z[s] = true;
    while (!Q.empty()) {
        int i = Q.front();
        Q.pop();
        for (vector<node>::iterator p = x[i].begin(); p != x[i].end(); ++p) {
            if (p->f > 0 && d[p->v] > d[i] + p->w) {
                d[p->v] = d[i] + p->w;
                fa[p->v] = i;
                ff[p->v] = p - x[i].begin();
                if (!z[p->v]) {
                    z[p->v] = true;
                    Q.push(p->v);
                }
            }
        }
        z[i] = false;
    }
    return d[t];
}

int Min_Cost(int s, int t, int n) {
    while (SPFA(s, t, n) < INF) {
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
