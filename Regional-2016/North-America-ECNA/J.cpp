#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MAXN = 110;

int N, M;
int Z[MAXN][MAXN];
vector<int> X[MAXN], Y[MAXN];

bool checker(int Z[], int M, vector<int> &X) {
    int L[M + 1];
    memset(L, 0, sizeof(L));
    for (int i = 1; i <= M; ++i) {
        if (Z[i] == 0) continue;
        L[i] = L[i - 1] + 1;
    }

    int f[M + 1][X.size() + 1];
    memset(f, 0, sizeof(f));
    f[0][0] = true;
    for (int i = 1; i <= M; ++i) {
        for (int j = 0; j <= X.size(); ++j) {
            if (Z[i] != 1) {
                f[i][j] |= f[i - 1][j];
                if (Z[i - 1] != 0 && j > 0 && L[i - 1] >= X[j - 1]) {
                    f[i][j] |= f[i - 1 - X[j - 1]][j - 1];
                }
            }
            if (Z[i] != 0 && i == M && j > 0 && L[i] >= X[j - 1]) {
                f[i][j] |= f[i - X[j - 1]][j - 1];
            }
        }
    }

    return f[M][X.size()];
}

bool valid(int Z[], int t, bool row) {
    bool flag = true;
    if (row) {
        flag = checker(Z, M, X[t]);
    } else {
        flag = checker(Z, N, Y[t]);
    }
    return flag;
}

bool tryupdate(int Z[], int t, bool row) {
    bool flag = false;
    if (row) {
        for (int i = 1; i <= M; ++i) {
            if (Z[i] != -1) continue;
            Z[i] = 1;
            if (!valid(Z, t, row)) {
                Z[i] = 0;
                flag = true;
                continue;
            }
            Z[i] = 0;
            if (!valid(Z, t, row)) {
                Z[i] = 1;
                flag = true;
                continue;
            }
            Z[i] = -1;
        }
    } else {
        for (int i = 1; i <= N; ++i) {
            if (Z[i] != -1) continue;
            Z[i] = 1;
            if (!valid(Z, t, row)) {
                Z[i] = 0;
                flag = true;
                continue;
            }
            Z[i] = 0;
            if (!valid(Z, t, row)) {
                Z[i] = 1;
                flag = true;
                continue;
            }
            Z[i] = -1;
        }
    }

    return flag;
}

int printG() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            switch (Z[i][j]) {
                case -1: cout << '?'; break;
                case  0: cout << '.'; break;
                case  1: cout << 'X'; break;
            }
        }
        cout << endl;
    }
    return 0;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        int A, B;
        cin >> A;
        while (A--) {
            cin >> B;
            X[i].push_back(B);
        }
    }

    for (int i = 1; i <= M; ++i) {
        int A, B;
        cin >> A;
        while (A--) {
            cin >> B;
            Y[i].push_back(B);
        }
    }

    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) Z[i][j] = -1;

    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 1; i <= N; ++i) {
            int CZ[MAXN];
            for (int j = 1; j <= M; ++j) CZ[j] = Z[i][j];
            if (tryupdate(CZ, i, 1)) {
                flag = true;
                for (int j = 1; j <= M; ++j) Z[i][j] = CZ[j];
            }
        }
        for (int j = 1; j <= M; ++j) {
            int CZ[MAXN];
            for (int i = 1; i <= N; ++i) CZ[i] = Z[i][j];
            if (tryupdate(CZ, j, 0)) {
                flag = true;
                for (int i = 1; i <= N; ++i) Z[i][j] = CZ[i];
            }
        }
    }
    printG();
    return 0;
}
