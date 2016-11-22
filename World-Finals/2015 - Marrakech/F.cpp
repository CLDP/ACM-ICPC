#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const int INF = 1000000000;

const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};

struct node {
    int x, y, l;
    node() {}
    node(int _x, int _y, int _l) {x = _x, y = _y, l = _l;}
};

int R, C;
string P[51];
string Q;
int f[51][51][10010];
vector<pair<int, int> > g[51][51];
bool z[51][51][10010];

bool inside(int a, int b) {
    return a >= 0 && b >= 0 && a < R && b < C;
}


int main() {
    cin >> R >> C;
    for (int i = 0; i < R; ++i) cin >> P[i];
    string Q;
    cin >> Q;
    Q = Q + "*";
    int QL = Q.size();
    
    queue<node> que;
    for (int i = 0; i < R; ++i)
     for (int j = 0; j < C; ++j) {
         for (int k = 0; k <= QL; ++k) f[i][j][k] = INF;
     }
     
    {
        node p;
        p.x = 0;
        p.y = 0;
        p.l = 0;
        while (p.l < QL && P[p.x][p.y] == Q[p.l]) ++p.l;
        f[p.x][p.y][p.l] = 0;
        z[p.x][p.y][p.l] = true;
        que.push(p);
    }
    
    for (int i = 0; i < R; ++i) 
     for (int j = 0; j < C; ++j) {
         int p = i, q = j;
         while (p >= 0 && P[p][q] == P[i][j]) --p;
         if (p >= 0) g[i][j].push_back(make_pair(p, q));
         
         p = i, q = j;
         while (p < R && P[p][q] == P[i][j]) ++p;
         if (p < R) g[i][j].push_back(make_pair(p, q));
         
         p = i, q = j;
         while (q >= 0 && P[p][q] == P[i][j]) --q;
         if (q >= 0) g[i][j].push_back(make_pair(p, q));
         
         p = i, q = j;
         while (q < C && P[p][q] == P[i][j]) ++q;
         if (q < C) g[i][j].push_back(make_pair(p, q));
     }
    
    while (!que.empty()) {
        node p = que.front();
        que.pop();
        if (p.l == QL) continue;
        for (int i = 0; i < g[p.x][p.y].size(); ++i) {
            int s = g[p.x][p.y][i].first;
            int t = g[p.x][p.y][i].second;
            int l = p.l;
            while (Q[l] == P[s][t]) ++l;
            if (z[s][t][l]) continue;
            f[s][t][l] = f[p.x][p.y][p.l] + 1;
            z[s][t][l] = true;
            que.push(node(s, t, l));
        }
    }
    
    int ans = INF;
    for (int i = 0; i < R; ++i)
     for (int j = 0; j < C; ++j) ans = min(f[i][j][QL], ans);
    
    cout << ans + QL << endl;
    return 0;
}
