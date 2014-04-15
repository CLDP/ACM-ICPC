#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int N, M, ans;
int x[3], y[3];
bool z[10][10], cz[10][10];

bool check(int a, int b) {
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < M; ++j) {
         if (z[i][j]) continue;
         if (i == 0 && j == 1) continue;
         int ans = 0;
         if (i > 0 && !z[i - 1][j]) ++ans;
         if (i < N - 1 && !z[i + 1][j]) ++ans;
         if (j > 0 && !z[i][j - 1]) ++ans;
         if (j < M - 1 && !z[i][j + 1]) ++ans;
         if (abs(a - i) + abs(b - j) == 1) ++ans;
         if (ans < 2) return false;
     }
     return true;
}

int dfs(int a, int b, int T) {
    if (T == N * M && a == 0 && b == 1) {
        ++ans;
        return 0;
    }
    if (abs(a) + abs(b - 1) > N * M - T) return 0;
    if (N * M / 4 >= T && abs(a - x[0]) + abs(b - y[0]) > N * M / 4 - T) return 0;
    if (N * M / 2 >= T && abs(a - x[1]) + abs(b - y[1]) > N * M / 2 - T) return 0;
    if (3 * N * M / 4 >= T && abs(a - x[2]) + abs(b - y[2]) > 3 * N * M / 4 - T) return 0;
    if (!check(a, b)) return 0;
    for (int i = 0; i < 4; ++i) {
        int p = a + MX[i], q = b + MY[i];
        if (p < 0 || p >= N || q < 0 || q >= M || z[p][q]) continue;
        z[p][q] = true;
        dfs(p, q, T + 1);
        z[p][q] = false;
    }
    return 0;
}

int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 0; i < 3; ++i) cin >> x[i] >> y[i];
        ans = 0;
        z[0][0] = true;
        dfs(0, 0, 1);
        z[0][0] = false;
        cout << "Case " << ++times << ": " << ans << endl;
    }
    return 0;
}
