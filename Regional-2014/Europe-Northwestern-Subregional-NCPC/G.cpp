#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

bool res[1005][1005];

int main() {
    int n, k;
    int f[1005];
    bool u[1005];
    vector<int> e[1005];
    
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
        u[i] = false;
        e[f[i]].push_back(i);
    }
    
    vector<pair<int, int> > p;
    for (int i = 1; i <= n; ++i) {
        if (u[i]) continue;
        vector<int> path;
        int j = i;
        while (true) {
            bool dup = false;
            for (int a = 0; a < path.size(); ++a)
                if (path[a] == j) {
                    dup = true;
                    break;
                }
            if (dup) break;
            path.push_back(j);
            j = f[j];
        }
        int jj = j;
        int cnt = 0;
        queue<int> cir;
        while (!u[jj]) {
            cnt++;
            cir.push(jj);
            u[jj] = true;
            jj = f[jj];
        }
        pair<int, int> pa;
        pa.first = cnt;
        while (!cir.empty()) {
            jj = cir.front();
            cir.pop();
            for (int a = 0; a < e[jj].size(); ++a)
                if (!u[e[jj][a]]) {
                    u[e[jj][a]] = true;
                    cir.push(e[jj][a]);
                    cnt++;
                }
        }
        pa.second = cnt;
        p.push_back(pa);
    }
    
    res[0][0] = true;
    for (int i = 0; i < p.size(); ++i) {
        for (int j = 0; j <= n; ++j) {
            if (!res[i][j]) continue;
            res[i + 1][j] = true;
            for (int a = p[i].first; a <= min(p[i].second, n - j); ++a)
                res[i + 1][j + a] = true;
        }
    }
    
    int fr = 0;
    for (int i = 1; i <= k; ++i)
        if (res[p.size()][i]) fr = i;
    
    cout << fr << endl;

    return 0;
}
