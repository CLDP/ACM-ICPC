#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
string P[110];

int dfs(int a, int b) {
    if (P[a][b] != '.') return 0;
    P[a][b] = '*';
    if (a > 0) {
        dfs(a - 1, b);
        if (b > 0 && P[a - 1][b] != '/') dfs(a - 1, b - 1);
        if (b < M - 1 && P[a - 1][b] != '\\') dfs(a - 1, b + 1);
    }
    if (a < N - 1) {
        dfs(a + 1, b);
        if (b > 0 && P[a + 1][b] != '\\') dfs(a + 1, b - 1);
        if (b < M - 1 && P[a + 1][b] != '/') dfs(a + 1, b + 1);
    }
    if (b > 0) dfs(a, b - 1);
    if (b < M - 1) dfs(a, b + 1);
    return 0;
}

int main() {
    freopen("ascii.in", "r", stdin);
    freopen("ascii.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> P[i];
    for (int i = 0; i < N; ++i) {
        dfs(i, 0);
        dfs(i, M - 1);
    }
    for (int i = 0; i < M; ++i) {
        dfs(0, i);
        dfs(N - 1, i);
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (P[i][j] == '.') ans += 2;
            if (P[i][j] == '/' || P[i][j] == '\\') ans += 1;
        }
    }
    cout << ans / 2 << endl;

    return 0;
}
