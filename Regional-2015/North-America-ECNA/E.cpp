#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

long long f[2][110];
vector<int> X[110];


int main() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        X[a].push_back(b);
        X[b].push_back(a);
    }
    bool curr = 0;
    f[0][S] = 1;
    while (T--) {
        curr = !curr;
        for (int i = 0; i < N; ++i) f[curr][i] = 0;
        for (int i = 0; i < N; ++i) {
            if (f[!curr][i] == 0) continue;
            for (int j = 0; j < X[i].size(); ++j) f[curr][X[i][j]] += f[!curr][i];
        }
    }
    long long ans = 0;
    for (int i = 0; i < N; ++i) ans += f[curr][i];
    cout << ans << endl;

    return 0;
}
