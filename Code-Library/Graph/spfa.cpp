const int MAXN = 100010;
const int INF = 1000000007;

int D[MAXN];
bool Z[MAXN];
vector<pair<int, int> > X[MAXN];

int SPFA(int s, int N) {
    for (int i = 1; i <= N; ++i) {
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
