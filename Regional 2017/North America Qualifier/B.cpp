#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 100010;
const long long INF = 1LL * 100000000 * 100000000;

long long D[MAXN];
bool Z[MAXN];
vector<pair<int, long long> > X[MAXN];

int SPFA(int s, int N) {
    for (int i = 0; i < N; ++i) {
        Z[i] = false;
        D[i] = INF;
    }
    D[s] = 0;
    Z[s] = true;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        Z[a] = false;
        for (int i = 0; i < X[a].size(); ++i) {
            if (D[X[a][i].first] > D[a] + X[a][i].second) {
                D[X[a][i].first] = D[a] + X[a][i].second;
                if (!Z[X[a][i].first]) {
                    Z[X[a][i].first] = true;
                    Q.push(X[a][i].first);
                }
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M, F, S, T;
    cin >> N >> M >> F >> S >> T;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        X[a].push_back(make_pair(b, c));
        X[b].push_back(make_pair(a, c));
    }
    SPFA(S, N);
    long long ans = D[T];
    for (int i = 0; i < F; ++i) {
        int a, b;
        cin >> a >> b;
        X[a].push_back(make_pair(b, 0));
        SPFA(S, N);
        if (D[T] < ans) ans = D[T];
        X[a].pop_back();
    }
    cout << ans << endl;

    return 0;
}
