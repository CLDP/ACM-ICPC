#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;

unordered_map<string, int> C;

int X[MAXN][MAXN];
int D[MAXN], L[MAXN];
bool Z[MAXN];


int main() {
    int N, M;
    cin >> N >> M;
    C["English"] = 1;
    for (int i = 0; i < N; ++i) {
        string P;
        cin >> P;
        C[P] = i + 2;
    }
    ++N;

    for (int i = 1; i <= N; ++i) {
        D[i] = L[i] = INF;
        for (int j = 1; j <= N; ++j) {
            if (i == j) continue;
            X[i][j] = INF;
        }
    }

    for (int i = 0; i < M; ++i) {
        string P, Q;
        int c;
        cin >> P >> Q >> c;
        int a = C[P], b = C[Q];
        X[a][b] = X[b][a] = c;
    }

    queue<int> Q;
    Q.push(1);
    D[1] = L[1] = 0;
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        if (Z[a]) continue;
        Z[a] = true;
        for (int i = 1; i <= N; ++i) {
            if (L[i] >= L[a] + 1 && D[i] > X[a][i]) {
                L[i] = L[a] + 1;
                D[i] = X[a][i];
                Q.push(i);
            }
        }
    }

    int ans = 0;
    for (int i = 2; i <= N; ++i) {
        if (D[i] == INF) {
            cout << "Impossible" << endl;
            return 0;
        }
        ans += D[i];
    }
    cout << ans << endl;

    return 0;
}
