#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50010;
const int INF = 1000000000;

struct node {
    int p, c, ind;
};


int N, M;
vector<pair<int, int> > x[MAXN];
vector<node> be[MAXN];
vector<pair<int, int> > res;
int dmin[MAXN], dmax[MAXN], cnt[MAXN], cn[MAXN];
bool z[MAXN];

int SPFA(int s, int t, int S, int d[]) {
    for (int i = 1; i <= N; ++i) {
        d[i] = INF;
        z[i] = false;
    }
    queue<int> que;
    que.push(1);
    d[1] = 0;
    z[1] = true;
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        z[a] = false;
        for (int i = 0; i < x[a].size(); ++i) {
            if (d[a] + x[a][i].second * S < d[x[a][i].first]) {
                d[x[a][i].first] = d[a] + x[a][i].second * S;
                if (!z[x[a][i].first]) {
                    z[x[a][i].first] = true;
                    que.push(x[a][i].first);
                }
            }
        }
    }
    if (S == -1) {
        for (int i = 1; i <= N; ++i) d[i] = -d[i];
    }
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) x[i].clear();
        for (int i = 1; i <= N; ++i) be[i].clear();
        for (int i = 1; i <= N; ++i) cnt[i] = 0;
        for (int i = 1; i <= N; ++i) cn[i] = -1;
        res.clear();
        node tn;
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            x[a].push_back(make_pair(b, c));
            tn.p = a;
            tn.c = c;
            tn.ind = i + 1;
            be[b].push_back(tn);
        }
        SPFA(1, N, 1, dmin);
        SPFA(1, N, -1, dmax);
        
        queue<pair<int, int> > qq;
        qq.push(make_pair(N, 0));
        bool sat = true;
        while (!qq.empty()) {
            int i = qq.front().first;
            int costNeed = qq.front().second;
            qq.pop();
            for (int j = 0; j < be[i].size(); ++j) {
                int k = be[i][j].p;
                if (dmin[k] == dmax[k]) {
                    if (costNeed + dmax[i] - dmax[k] - be[i][j].c > 0)
                        res.push_back(make_pair(be[i][j].ind, costNeed + dmax[i] - dmax[k] - be[i][j].c));
                } else {
                    int ncn = costNeed + dmax[i] - dmax[k] - be[i][j].c;
                    if (cn[k] == -1) {
                        cn[k] = ncn;
                    } else 
                    if (cn[k] != ncn) {
                        sat = false;
                        break;
                    }
                    ++cnt[k];
                    if (cnt[k] == x[k].size()) qq.push(make_pair(k, cn[k]));
                }
            }
            if (!sat) break;
        }
        
        ++times;
        if (!sat)
            cout << "Case " << times << ": No solution\n";
        else {
            cout << "Case " << times << ": " << res.size() << " " << dmax[N] << endl;
            for (int i = 0; i < res.size(); ++i)
                cout << res[i].first << " " << res[i].second << endl;
        }
    }
    return 0;
}
