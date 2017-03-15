#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAXN = 2510;
const double EPS = 1e-6;
const double NINF = -1e100;

struct node {
    int s, p;
    double W;
};

int K, N;
node Y[MAXN];
vector<int> X[MAXN];
bool z[MAXN][MAXN];
double f[MAXN][MAXN];
int S[MAXN];

double dp(int a, int b, int fa, int t) {
    if (b == 0) return 0;
    if (S[a] < b) return NINF;
    if (z[a][b]) return f[a][b];
    z[a][b] = true;
    if (X[fa].size() == t) {
        if (X[a].size() == 0) {
            if (b != 1) f[a][b] = NINF; else f[a][b] = Y[a].W;
            return f[a][b];
        }
        f[a][b] = dp(X[a][0], b - 1, a, 1) + Y[a].W;
        return f[a][b];
    }
    if (X[a].size() == 0) {
        f[a][b] = max(dp(X[fa][t], b - 1, fa, t + 1) + Y[a].W, dp(X[fa][t], b, fa, t + 1));
        return f[a][b];
    }
    f[a][b] = dp(X[fa][t], b, fa, t + 1);
    for (int i = 1; i <= b; ++i) {
        if (S[X[a][0]] >= i - 1 && S[X[fa][t]] >= b - i)
            f[a][b] = max(f[a][b], dp(X[a][0], i - 1, a, 1) + dp(X[fa][t], b - i, fa, t + 1) + Y[a].W);
    }
    return f[a][b];
}

void dfs(int a) {
    S[a] = 1;
    for (int i = 0; i < X[a].size(); ++i) {
        dfs(X[a][i]);
        S[a] += S[X[a][i]];
    }
    if (X[a].size() < 2) return ;
    for (int i = X[a].size() - 2; i >= 0; --i) S[X[a][i]] += S[X[a][i + 1]];
}

int main() {
    cin >> K >> N;
    for (int i = 1; i <= N; ++i) {
        int r;
        cin >> Y[i].s >> Y[i].p >> r;
        X[r].push_back(i);
    }
    dfs(0);
    int root = X[0][0];
    double L = 0.0001, R = 10001;
    while (L + EPS < R) {
        double mid = (L + R) / 2;
        memset(f, 0, sizeof(f));
        memset(z, 0, sizeof(z));
        for (int i = 1; i <= N; ++i) Y[i].W = Y[i].p - Y[i].s * mid;
        dp(root, K, 0, 1);
        if (f[root][K] >= 0) L = mid; else R = mid;
    }

    cout << fixed << setprecision(3) << R << endl;

    return 0;
}
