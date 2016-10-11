#include <iostream>
#include <vector>
using namespace std;

int P1, P2;

int X[11][11];
char C[11][11];

inline int cal(const int &a, const int &b, const char &c) {
    switch (c) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
    }
    return 0;
}

int dfs(const int &N, const bool &trymax, const bool &first) {
    if (N == 0) return X[N][0];
    int ans = 0;
    bool flag = false;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            X[N - 1][j] = X[N][j];
            C[N - 1][j] = C[N][j];
        }

        X[N - 1][i] = cal(X[N][i], X[N][i + 1], C[N][i]);
        for (int j = i + 2; j < N + 1; ++j) X[N - 1][j - 1] = X[N][j];
        for (int j = i + 1; j < N; ++j) C[N - 1][j - 1] = C[N][j];

        int temp = dfs(N - 1, !trymax, false);
        if (trymax) {
            if (!flag || temp > ans) {
                ans = temp;
                flag = true;
                if (first) P1 = i;
            }
        } else {
            if (!flag || temp < ans) {
                ans = temp;
                flag = true;
                if (first) P2 = i;
            }
        }

    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int times = 1; times <= T; ++times) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) cin >> X[N][i] >> C[N][i];
        cin >> X[N][N];

        int A = dfs(N, true, true);
        int B = dfs(N, false, true);
        cout << "Case " << times << ":" << endl;
        cout << "Player 1 (" << X[N][P1] << C[N][P1] << X[N][P1 + 1] << ") leads to " << A << endl;
        cout << "Player 2 (" << X[N][P2] << C[N][P2] << X[N][P2 + 1] << ") leads to " << B << endl;
        if (A > -B) {
            cout << "Player 1 wins" << endl;
        } else
        if (A < -B) {
            cout << "Player 2 wins" << endl;
        } else {
            cout << "Tie" << endl;
        }
    }
    return 0;
}
