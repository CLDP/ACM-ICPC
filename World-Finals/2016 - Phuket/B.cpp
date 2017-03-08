#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5010;
const int INF = 1000000007;

vector<pair<int, int> > X[MAXN], Y[MAXN];
int D[MAXN];

int Dijkstra(vector<pair<int, int> > X[], int N, int s) {
    vector<int> d(N + 1, INF);
    vector<bool> z(N + 1, false);
    d[s] = 0;
    for (int i = 0; i < N; ++i) {
        int a = -1, b = INF;
        for (int j = 1; j <= N; ++j) {
            if (z[j]) continue;
            if (d[j] < b) {
                b = d[j];
                a = j;
            }
        }
        z[a] = true;
        for (int j = 0; j < X[a].size(); ++j) {
            d[X[a][j].first] = min(d[X[a][j].first], d[a] + X[a][j].second);
        }
    }
    for (int i = 1; i <= N; ++i) D[i] += d[i];
    return 0;
}

int g[MAXN][MAXN];
long long f[MAXN][MAXN];
long long sum[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, B, S, R;
    cin >> N >> B >> S >> R;
    for (int i = 0; i < R; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        X[a].push_back(make_pair(b, c));
        Y[b].push_back(make_pair(a, c));
    }

    Dijkstra(X, N, B + 1);
    Dijkstra(Y, N, B + 1);
    sort(D + 1, D + B + 1);

    for (int i = 1; i <= B; ++i) {
        sum[i] = sum[i - 1] + D[i];
        f[i][1] = sum[i] * (i - 1);
        g[i][1] = 1;
    }

    for (int j = 2; j <= S; ++j) {
        f[B][j] = f[B][j - 1];
        g[B][j] = B;
        for (int k = 2; k <= B; ++k) {
            long long temp = f[k - 1][j - 1] + (sum[B] - sum[k - 1]) * (B - k);
            if (temp < f[B][j]) {
                f[B][j] = temp;
                g[B][j] = k;
            }
        }
        for (int i = B - 1; i >= j; --i) {
            f[i][j] = f[i][j - 1];
            g[i][j] = i;
            for (int k = g[i][j - 1]; k <= g[i + 1][j]; ++k) {
                long long temp = f[k - 1][j - 1] + (sum[i] - sum[k - 1]) * (i - k);
                if (temp < f[i][j]) {
                    f[i][j] = temp;
                    g[i][j] = k;
                }
            }
        }
    }
    cout << f[B][S] << endl;
    return 0;
}
