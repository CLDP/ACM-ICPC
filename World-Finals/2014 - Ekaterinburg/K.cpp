#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2000010;

int x[MAXN], y[MAXN], z[MAXN];
int A[MAXN][22], B[MAXN][22];

int query(int a, int b) {
    int i = 0;
    while (a + ((1 << (i + 1)) - 1) <= b) ++i;
    return max(A[a][i], A[b - (1 << i) + 1][i]);
}

bool check(int temp, int xi, int N) {
    if (temp < xi) temp += N;
    return temp >= xi + N - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    int M = K;
    for (int i = 1; i <= M; ++i) {
        cin >> x[i] >> y[i];
        if (x[i] > y[i]) y[i] += N;

        A[x[i]][0] = max(A[x[i]][0], y[i]);
        int a = z[y[i]];
        if (y[i] - x[i] >= y[a] - x[a]) z[y[i]] = i;

        if (y[i] <= N) {
            ++K;
            x[K] = x[i] + N;
            y[K] = y[i] + N;
            A[x[K]][0] = max(A[x[K]][0], y[K]);
            a = z[y[K]];
            if (y[K] - x[K] >= y[a] - x[a]) z[y[K]] = K;
        }

    }

    for (int i = 1; i < 22; ++i) {
        for (int j = 1; j <= N + N; ++j) {
            if (j + (1 << i) - 1 > N + N) {
                A[j][i] = A[j][i - 1];
            } else {
                A[j][i] = max(A[j][i - 1], A[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
  
    for (int i = 1; i <= K; ++i) {
        int a = 0;
        if (x[i] <= y[i]) a = query(x[i], y[i] + 1); else a = query(x[i], y[i] + N + 1);
        B[i][0] = z[a];
    }
    for (int i = 1; i < 22; ++i) {
        for (int j = 1; j <= K; ++j) {
            B[j][i] = B[B[j][i - 1]][i - 1];
        }
    }

    int ans = K + 1;
    for (int i = 1; i <= M; ++i) {
        if (!check(y[B[i][21]], x[i], N)) continue;
        if (x[i] + N - 1 == y[i]) {
            ans = 1;
            continue;
        }

        int a = i, j = 21, temp = 0;
        while (j >= 0) {
            while (j >= 0 && check(y[B[a][j]], x[i], N)) --j;
            if (j >= 0) temp += (1 << j); else break;
            a = B[a][j];
        }
        ans = min(ans, temp + 2);
    }

    if (ans == K + 1) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
