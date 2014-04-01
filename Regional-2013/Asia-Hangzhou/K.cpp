#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

class node {
public:
    int v, c, w;  // node   capacity    cost  
    node *next, *pair;
};

const int MAXN = 1010;
const int INF = 1000000000;


node *x[MAXN];
int n, m, flow, cost, dist[MAXN];
int s, t;
bool z[MAXN];
int Si[110], Ti[110], Cij[110][110], Dij[110][110], Eij[110][110], Fij[110][110];


int newnode(int s, int t, int w, int c = INF) {
    node xs = {t, c, w, x[s], 0}, xt = {s, 0, -w, x[t], 0};
    x[s] = new node(xs);
    x[t] = new node(xt);
    x[s]->pair = x[t];
    x[t]->pair = x[s];
    return 0;
}

int augment(int now, int m) {
    if (now == t) return cost += dist[s]*m, flow += m, m;
    z[now] = true;
    for (node *p = x[now]; p; p = p->next)
     if (p->c && !z[p->v] && dist[p->v] + p->w == dist[now]) 
      if (int d = augment(p->v, m < p->c ? m : p->c))
       return p->c -= d, p->pair->c += d, d;
    return 0;
}

bool relabel() {
    int d = INF, w;
    for (int i = 1; i <= n; ++i) if (z[i]) 
     for (node *p = x[i]; p; p = p->next)
      if (p->c && !z[p->v]) 
       if ((w = p->w - dist[i] + dist[p->v]) < d) d = w;
    if (d == INF) return 0;
    for (int i = 1; i <= n; ++i) 
     if (z[i]) dist[i] += d;
    return 1;
}

int mincost() {
    flow = cost = 0;
    memset(dist, 0, sizeof(dist));
    do 
        do 
            memset(z,0,sizeof(z));
        while (augment(s,INF));
    while (relabel());
    return 0;
}


int main() {
    int N, M, K;
    while (cin >> N >> M >> K) {
        if (N + M + K == 0) break;
        for (int i = 1; i <= N; ++i) cin >> Si[i] >> Ti[i];
        for (int i = 1; i <= N; ++i) 
         for (int j = 1; j <= M; ++j) cin >> Cij[i][j];
        for (int i = 1; i <= N; ++i) 
         for (int j = 1; j <= M; ++j) cin >> Dij[i][j];
        for (int i = 1; i <= N; ++i) 
         for (int j = 1; j <= N; ++j) cin >> Eij[i][j];
        for (int i = 1; i <= N; ++i) 
         for (int j = 1; j <= N; ++j) cin >> Fij[i][j];
        n = M + N + N + N + 2;
        s = n - 1, t = n;
        for (int i = 1; i <= n; ++i) x[i] = NULL;
        flow = cost = 0;
        memset(dist, 0, sizeof(dist));
        
        int C1 = M, C2 = M + N, C3 = M + N + N;
        for (int i = 1; i <= M; ++i) newnode(s, i, 0, 1);
        for (int i = 1; i <= N; ++i) newnode(s, C1 + i, 0, 1);
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) {
             if (Cij[i][j] <= Si[i]) {
                 newnode(j, C2 + i, Dij[i][j], 1);
             } else
             if (Cij[i][j] < Ti[i]) {
                 newnode(j, C2 + i, Dij[i][j] + K * (Cij[i][j] - Si[i]), 1);
             }
         }
        
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) {
             if (i == j) continue;
             if (Ti[i] + Eij[i][j] <= Si[j]) {
                 newnode(C1 + i, C3 + j, Fij[i][j], 1);
             } else
             if (Ti[i] + Eij[i][j] < Ti[j]) {
                 newnode(C1 + i, C3 + j, Fij[i][j] + K * (Ti[i] + Eij[i][j] - Si[j]), 1);
             }
         }
        
        for (int i = 1; i <= N; ++i) {
            newnode(C2 + i, C3 + i, 0, 1);
            newnode(C3 + i, t, 0, 1);
        }
        mincost();
        if (flow < N) cost = -1;
        cout << cost << endl;
    }
    return 0;
}
