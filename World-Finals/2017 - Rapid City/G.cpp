#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 310;

string X[MAXN], Y[MAXN];

bool cal(int N, int M, int a, int b) {
    int ans = 0;
    for (int i = a - 1; i <= a + 1; ++i) {
        if (i < 1 || i > N - 2) continue;
        for (int j = b - 1; j <= b + 1; ++j) {
            if (j < 1 || j > M - 2) continue;
            ans += Y[i][j] == '#';
        }
    }
    return ans % 2 == 1;
}

int geta(int N, int M) {
    for (int i = 0; i < N; ++i) Y[i] = string(M, '.');
    for (int i = 0; i < N - 2; ++i) {
        for (int j = 0; j < M - 2; ++j) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) Y[i + 1][j + 1] = '#';
        }
        for (int j = M - 2; j < M; ++j) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) return i;
        }
    }
    for (int i = N - 2; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) return i;
        }
    }
    return -1;
}

int getb(int N, int M) {
    for (int i = 0; i < N; ++i) Y[i] = string(M, '.');
    for (int j = 0; j < M - 2; ++j) {
        for (int i = 0; i < N - 2; ++i) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) Y[i + 1][j + 1] = '#';
        }
        for (int i = N - 2; i < N; ++i) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) return j;
        }
    }
    for (int j = M - 2; j < M; ++j) {
        for (int i = 0; i < N; ++i) {
            bool odd = cal(N, M, i, j);
            if (odd != (X[i][j] == '#')) return j;
        }
    }
    return -1;
}

void update(int &N, int &M) {
    for (int i = 0; i < N - 2; ++i) X[i] = Y[i + 1].substr(1, M - 2);
    N -= 2;
    M -= 2;
}

void clear(int &N, int &M) {
    int a = N, b = 0, c = M, d = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (X[i][j] == '.') continue;
            a = min(a, i);
            b = max(b, i);
            c = min(c, j);
            d = max(d, j);
        }
    }
    for (int i = a; i <= b; ++i) {
        X[i - a] = X[i].substr(c, d - c + 1);
    }
    N = b - a + 1;
    M = d - c + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> M >> N;
    for (int i = 0; i < N; ++i) cin >> X[i];
    while (N > 2 && M > 2) {
        int a = -1, b = -1;
        a = geta(N, M);
        if (a == -1) {
            update(N, M);
            continue;
        }
        b = getb(N, M);
        char &C = X[a][b];
        if (C == '.') C = '#'; else C = '.';
        a = geta(N, M);
        if (a != -1) {
            if (C == '.') C = '#'; else C = '.';
            break;
        }
        update(N, M);
        clear(N, M);
        continue;
    }

    for (int i = 0; i < N; ++i) cout << X[i] << endl;
    return 0;
}
