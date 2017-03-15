#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const long long INF = 1LL * 100000000 * 100000000;

struct node {
    long long x, y, w;
    bool operator < (const node &B) const {
        return x > B.x;
    }
};

int N, K;
node X[MAXN], Y[MAXN];
vector<int> Z[MAXN];
long long ans = INF;

void dfs(int a, int M, long long temp) {
    if (K - M > N - a || temp > ans) return ;
    if (a == N) {
        ans = min(ans, temp);
        return ;
    }
    for (int i = 0; i < M; ++i) {
        node prev = Y[i];
        Y[i].x = max(Y[i].x, X[a].x);
        Y[i].y = max(Y[i].y, X[a].y);
        Y[i].w += X[a].w;
        Z[i].push_back(a);
        dfs(a + 1, M, temp + (Y[i].x * Y[i].y - prev.x * prev.y) * prev.w 
                           + (Y[i].x * Y[i].y - X[a].x * X[a].y) * X[a].w);
        Z[i].pop_back();
        Y[i] = prev;
    }
    if (M < K) {
        Y[M] = X[a];
        Z[M].push_back(a);
        dfs(a + 1, M + 1, temp);
        Z[M].pop_back();
    }
}

int main() {
    cin >> N >> K;
    if (K > N) K = N;
    for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y >> X[i].w;
    sort(X, X + N);
    dfs(0, 0, 0);
    cout << ans << endl;

    return 0;
}
