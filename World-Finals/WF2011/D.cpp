#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 150;

int N, Cost;
int C[MAXN][MAXN], W[MAXN][MAXN];
string X[MAXN];


int newnode(int a, int b, int f, int c) {
    C[a][b] = f;
    W[a][b] = c;
    W[b][a] = -c;
    return 0;
}

int addnode(int a, int b, int c) {
    C[a][b] += c;
    return 0;
}

int Build(int A, int B, int &Must, int &Can) {
    memset(C, 0, sizeof(C));
    memset(W, 0, sizeof(W));
    Must = Can = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) {
         char r = X[i - 1][j - 1];
         if (r =='C') {
             ++Must;
             newnode(i, j + N, 1, -10000);
         } else 
         if (r == '.') {
             ++Can;
             newnode(i, j + N, 1, -1);
         }
    }
    for (int i = 1; i <= N; ++i) {
        newnode(i + N + N, i, Must * A / B, 0);
        newnode(i + N, i + N + N, 10000, 0);
    }
    return 0;
}


bool FindCir() {
    queue<int> que;
    vector<int> d(3 * N + 1, 0), f(3 * N + 1, 0), cnt(3 * N + 1, 0);
    vector<bool> z(3 * N + 1, false);
    for (int i = 1; i <= 3 * N; ++i) que.push(i);
    
    while (!que.empty()) {
        int A = que.front();
        que.pop();
        ++cnt[A];
        for (int i = 1; i <= 3 * N; ++i)
         if (C[A][i] > 0 && d[i] > d[A] + W[A][i]) {
             d[i] = d[A] + W[A][i];
             f[i] = A;
             if (!z[i]) {
                 z[i] = true;
                 que.push(i);
             }
         }
         
        if (cnt[A] > 3 * N) {
            int p;
            vector<int> cc(3 * N + 1, 0);
            for (int i = A; ; i = f[i]) {
                ++cc[i];
                if (cc[i] == 2) {
                    p = i;
                    break;
                }
            }
            for (int i = p; ; i = f[i]) {
                --C[f[i]][i];
                ++C[i][f[i]];
                Cost += W[f[i]][i];
                if (f[i] == p) break;
            }
            return true;
        }
        z[A] = false;
    }
    return false;
}


int main() {
    int times = 0, A, B;
    while (cin >> N >> A >> B) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> X[i];
        cout << "Case " << ++times << ": ";
        int Must, Can;
        Build(A, B, Must, Can);
        Cost = 0;
        if (Can == N * N && N * N * A >= N * B) {
            cout << N * N << endl;
            continue;
        }
        
        int ans = -1, Upper = Must * A / B;
        for (int i = Must; i <= Must + Can; ++i) {
            if (i != 0 && B > A * N) break;
            if (i > 0) {
                for (int j = 1; j <= N; ++j) addnode(j + N + N, j, i * A / B - Upper);
                Upper = i * A / B;
            }
            while (FindCir()) ;
            int P = -Cost / 10000, Q = -Cost % 10000;
            if (P != Must) continue;
            if (P + Q >= i) {
                ans = P + Q;
                i = ans;
            }
        }
        if (ans == -1) cout << "impossible" << endl; else cout << ans - Must << endl;
    }
    return 0;
}
