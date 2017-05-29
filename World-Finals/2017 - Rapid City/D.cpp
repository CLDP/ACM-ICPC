#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 500010;

struct node {
    int x, y;
    bool operator < (const node &B) const {
        if (x != B.x) return x < B.x;
        return y < B.y;
    }
};

node X[MAXN], Y[MAXN];
long long ans;

bool check(int a, int M) {
    int p = lower_bound(Y, Y + M, X[a]) - Y;
    if (p == M) return false;
    return Y[p].y > X[a].y;
}

void solve(int a, int b, int c, int d) {
    int mid = (a + b) / 2;
    long long temp = 0;
    int p = -1;
    for (int i = c; i <= d; ++i) {
        if (Y[i].x <= X[mid].x || Y[i].y <= X[mid].y) continue;
        if (1LL * (X[mid].x - Y[i].x) * (X[mid].y - Y[i].y) >= temp) {
            temp = 1LL * (X[mid].x - Y[i].x) * (X[mid].y - Y[i].y);
            p = i;
        }
    }
    ans = max(ans, temp);
    if (a == b) return ;
    if (a <= mid - 1) solve(a, mid - 1, c, p);
    if (mid + 1 <= b) solve(mid + 1, b, p, d);
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y;
    for (int i = 0; i < M; ++i) cin >> Y[i].x >> Y[i].y;

    sort(X, X + N);
    sort(Y, Y + M);
    int r = 1;
    for (int i = 1; i < M; ++i) {
        while (r > 0 && Y[i].y >= Y[r - 1].y) --r;
        Y[r++] = Y[i];
    }
    M = r;
    r = 1;
    for (int i = 1; i < N; ++i) {
        if (X[i].x == X[r - 1].x) continue;
        if (X[i].y > X[r - 1].y) continue;
        X[r++] = X[i];
    }
    N = r;  
    r = 0;
    for (int i = 0; i < N; ++i) {
        if (check(i, M)) X[r++] = X[i];
    }
    N = r;

    if (N != 0 && M != 0) solve(0, N - 1, 0, M - 1);
    cout << ans << endl;
    return 0;
}
