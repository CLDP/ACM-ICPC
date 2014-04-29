#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 310;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXM];
int g[MAXN], f[MAXN][MAXM], tmp[MAXM], mid;

int update(int &a, int b) {
    if (b > a) a = b;
    return 0;
}

bool check(int a) {
    if (a >= -mid && a <= mid) return true;
    return false;
}

int dfs(int a, int fa) {
    for (int i = 0; i <= mid; ++i) f[a][i] = -INF;
    f[a][0] = 0;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first == fa) continue;
        dfs(x[a][i].first, a);
        for (int j = 0; j <= mid; ++j) {
            tmp[j] = f[a][j];
            f[a][j] = -INF;
        }
        int b = x[a][i].first;
        for (int j = 0; j <= mid; ++j) {
            if (tmp[j] == -INF) continue;
            for (int k = 0; k <= mid; ++k) {
                if (f[b][k] == -INF) continue;
                if (check(j + k - x[a][i].second) && check(tmp[j] + f[b][k] - x[a][i].second))
                    update(f[a][max(j, k - x[a][i].second)], min(tmp[j], f[b][k] - x[a][i].second));
                x[a][i].second -= 60;
                if (check(j + k - x[a][i].second) && check(tmp[j] + f[b][k] - x[a][i].second))
                    update(f[a][max(j, k - x[a][i].second)], min(tmp[j], f[b][k] - x[a][i].second));
                x[a][i].second += 60;
            }
        }
    }
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first != fa) dfs(x[a][i].first, a);
    }
    
    return 0;
}

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) {
            g[i] = 0;
            x[i].clear();
        }
        for (int i = 1; i < N; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            c = c % 60;
            x[a].push_back(make_pair(b, c));
            x[b].push_back(make_pair(a, c));
        }
        int l = -1, r = 300;
        while (l + 1 < r) {
            mid = (l + r) / 2;
            dfs(1, 0);
            int i;
            for (i = 0; i <= mid; ++i)
             if (f[1][i] > -INF) break;
            if (i == mid + 1) l = mid; else r = mid;
        }
        cout << "Case " << ++times << ": " << r << endl;
    }
    return 0;
}
