#include <iostream>
#include <set>
#include <cstring>
using namespace std;

const int MAXN = 105;

int X[MAXN][MAXN], L[MAXN], F[MAXN];
int l[MAXN], x[MAXN][MAXN];
bool z[MAXN];

bool find(int v, int M) {
    int k;
    for (int i = 1; i <= M; ++i) {
        if (!z[i] && x[v][i]) {
            z[i] = 1;
            k = l[i];
            l[i] = v;
            if (!k || find(k, M)) return 1;
            l[i] = k;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    set<int> S;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> X[i][j];
            S.insert(X[i][j]);
            L[i] = max(L[i], X[i][j]);
            F[j] = max(F[j], X[i][j]);
        }
    }

    long long ans = 0, nonzero = 0;
    for (auto iter = S.rbegin(); iter != S.rend(); ++iter) {
        if (*iter == 0) break;
        int Ni = 0, Mi = 0;
        for (int i = 1; i <= N; ++i) {
            if (L[i] == *iter) ++Ni;
        }
        for (int j = 1; j <= M; ++j) {
            if (F[j] == *iter) ++Mi;
        }
        if (Ni + Mi == 0) continue;

        memset(x, 0, sizeof(x));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (X[i][j] == 0) continue;
                if (L[i] == *iter && F[j] == *iter) x[i][j] = 1;
            }
        }

        memset(l, 0, sizeof(l));
        for (int i = 1; i <= N; ++i) {
            memset(z, 0, sizeof(z));
            find(i, M);
        }
        int cnt = 0;
        for (int i = 1; i <= M; ++i) cnt += (l[i] > 0);
        ans += 1LL * (*iter) * (Ni + Mi - cnt);
        nonzero += Ni + Mi - cnt;
    }

    ans = -ans + nonzero;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (X[i][j] > 0) {
                ans += X[i][j] - 1;
                continue;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
