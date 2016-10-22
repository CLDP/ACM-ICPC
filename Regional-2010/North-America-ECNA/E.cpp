#include <iostream>
#include <vector>
using namespace std;



int main() {
    int M, N, times = 0;
    while (cin >> M >> N) {
        ++times;
        if (N == 0 && M == 0) break;
        vector<vector<int> > X(M, vector<int>(N)), Y;
        int K;
        cin >> K;
        for (int i = 0; i < K; ++i) {
            int a, b;
            cin >> a >> b;
            X[a][b] = 1;
        }
        cin >> K;
        while (K--) {
            Y = vector<vector<int> >(M, vector<int>(N, 0));
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    int ans = 0;
                    if (i == 0) {
                        for (int k = N / 2 - 1; k <= N / 2 + 1; ++k) ans += X[i][(j + k) % N];
                    } else {
                        for (int k = N - 1; k <= N + 1; ++k) ans += X[i - 1][(j + k) % N];
                    }
                    if (i == M - 1) {
                        for (int k = N / 2 - 1; k <= N / 2 + 1; ++k) ans += X[i][(j + k) % N];
                    } else {
                        for (int k = N - 1; k <= N + 1; ++k) ans += X[i + 1][(j + k) % N];
                    }
                    ans += X[i][(j + 1) % N];
                    ans += X[i][(j + N - 1) % N];
                    Y[i][j] = X[i][j];
                    if (X[i][j] == 0) {
                        if (ans == 3) Y[i][j] = 1;
                    } else {
                        if (ans < 2 || ans > 3) Y[i][j] = 0;
                    }
                }
            }
            X = Y;
        }

        int ans = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) ans += X[i][j];
        }
        cout << "Case " << times << ": " << ans;
        if (ans == 0) {
            cout << " -1 -1 -1 -1" << endl;
            continue;
        }
        bool flag = true;
        int A = 0, B = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (flag && X[i][j]) {
                    flag = false;
                    cout << " " << i << " " << j;
                }
                if (X[i][j]) {
                    A = i;
                    B = j;
                }
            }
        }
        cout << " " << A << " " << B << endl;
    }
    return 0;
}
