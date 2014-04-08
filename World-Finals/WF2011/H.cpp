#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50010;

vector<int> x[MAXN];
int low[MAXN], dfn[MAXN];
bool z[MAXN], cz[MAXN];
set<int> SS;

int dfs(int a, int f, int &time) {
    dfn[a] = low[a] = time;
    int s = 0;
    bool flag = false;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == f) continue;
        if (dfn[x[a][i]] == 0) {
            dfs(x[a][i], a, ++time);
            ++s;
            low[a] = min(low[a], low[x[a][i]]);
            if (low[x[a][i]] >= dfn[a]) flag = true;
        } else {
            low[a] = min(low[a], dfn[x[a][i]]);
        }
    }
    if ((f != -1 && flag) || (f == -1 && s > 1)) z[a] = true;
    return 0;
}


int dfsC(int a) {
    int ans = 1;
    z[a] = true;
    for (int i = 0; i < x[a].size(); ++i) {
        if (z[x[a][i]]) {
            if (cz[x[a][i]]) SS.insert(x[a][i]);
            continue;
        }
        ans += dfsC(x[a][i]);
    }
    return ans;
}

int main() {
    int M, times = 0;
    while (cin >> M) {
        if (M == 0) break;
        int N = 0, a, b;
        for (int i = 1; i <= 50000; ++i) x[i].clear();
        for (int i = 0; i < M; ++i) {
            cin >> a >> b;
            N = max(N, a);
            N = max(N, b);
            x[a].push_back(b);
            x[b].push_back(a);
        }
        
        memset(z, 0, sizeof(z));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        a = 1;
        dfs(1, -1, a);
        
        a = 0;
        for (int i = 1; i <= N; ++i) {
            a += z[i];
            cz[i] = z[i];
        }
        
        cout << "Case " << ++times << ": ";
        if (a == 0) {
            long long ans = N;
            ans = ans * (ans - 1) / 2;
            cout << "2 " << ans << endl;
            continue;
        }
        unsigned long long ans = 1, cnt = 0;
        for (int i = 1; i <= N; ++i) {
            if (z[i]) continue;
            SS.clear();
            int temp = dfsC(i);
            if (SS.size() > 1) continue;
            ans = ans * temp;
            ++cnt;
        }
        cout << cnt << " " << ans << endl;
    }
    
    return 0;
}
