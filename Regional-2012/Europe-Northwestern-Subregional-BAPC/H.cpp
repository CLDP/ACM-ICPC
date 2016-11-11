#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


const int INF = 100000000;


vector<pair<int, int> > X;
int f[1010][1010];

struct node {
    int x, y, d;
    node(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}
    bool operator < (node const &B) const {
        return d > B.d;
    }
};

int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, M, T;
        cin >> T >> M >> N;
        X = vector<pair<int, int> > (T, make_pair(0, 0));
        for (int i = 0; i < T; ++i) cin >> X[i].second >> X[i].first;
        if (T >= N * M - 1) {
            cout << 0 << endl;
            continue;
        }
        if (T == 0) {
            cout << N + M - 2 << endl;
            continue;
        }
        memset(f, -1, sizeof(f));
        queue<pair<int, int> > Q;
        for (int i = 0; i < T; ++i) {
            Q.push(make_pair(X[i].first, X[i].second));
            f[X[i].first][X[i].second] = 0;
        }
        while (!Q.empty()) {
            int a = Q.front().first, b = Q.front().second;
            if (a > 0 && f[a - 1][b] == -1) {
                f[a - 1][b] = f[a][b] + 1;
                Q.push(make_pair(a - 1, b));
            }
            if (a < N - 1 && f[a + 1][b] == -1) {
                f[a + 1][b] = f[a][b] + 1;
                Q.push(make_pair(a + 1, b));
            }
            if (b > 0 && f[a][b - 1] == -1) {
                f[a][b - 1] = f[a][b] + 1;
                Q.push(make_pair(a, b - 1));
            }
            if (b < M - 1 && f[a][b + 1] == -1) {
                f[a][b + 1] = f[a][b] + 1;
                Q.push(make_pair(a, b + 1));
            }
            Q.pop();
        }
        vector<node> Y;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) Y.push_back(node(i, j, f[i][j]));
        sort(Y.begin(), Y.end());
        
        int ans = 0;
        int minXPY = INF, maxXPY = -INF, minXMY = INF, maxXMY = -INF;
        for (int i = 0; i < Y.size(); ) {
            if (Y[i].d == 0) break;
            int j = i;
            while (Y[i].d == Y[j].d) {
                minXPY = min(minXPY, Y[j].x + Y[j].y);
                maxXPY = max(maxXPY, Y[j].x + Y[j].y);
                minXMY = min(minXMY, Y[j].x - Y[j].y);
                maxXMY = max(maxXMY, Y[j].x - Y[j].y);
                ++j;
            }
            int temp = 0;
            temp = max(temp, maxXPY - minXPY);
            temp = max(temp, maxXMY - minXMY);
            ans = max(ans, min(temp, Y[i].d));
            i = j;
        }
        
        cout << ans << endl;
    }
    return 0;
}
