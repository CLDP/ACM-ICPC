#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 210;

long long X[MAXN], Y[MAXN];
int N;
long long D;
int l[MAXN];
bool z[MAXN], cz[MAXN], x[MAXN][MAXN];

long long dist(int a, int b) {
    return (X[a] - X[b]) * (X[a] - X[b]) + (Y[a] - Y[b]) * (Y[a] - Y[b]);
}

bool find(int v, int M) {
    int k;
    for (int i = 1; i <= M; ++i) 
     if (!z[i] && x[v][i]) {
         z[i] = 1;
         k = l[i];
         l[i] = v;
         if (!k || find(k, M)) return 1;
         l[i] = k;
     }
    return 0;
}

bool check(int a, int N, int M, bool flag) {
    if (flag) {
        for (int i = 1; i <= M; ++i) 
         if (x[a][i]) return false;
        return true;
    }
    for (int i = 1; i <= N; ++i)
     if (x[i][a]) return false;
    return true;
}

int getside(int t, int a, int b) {
    if (dist(a, t) > dist(a, b)) return 2;
    if (dist(b, t) > dist(a, b)) return 2;
    long long K = (X[a] - X[b]) * (Y[a] - Y[t]) - (Y[a] - Y[b]) * (X[a] - X[t]);
    if (K > 0) return 1;
    if (K < 0) return -1;
    return 0;
}

int dfs(int a, int N, int M, bool flag) {
    if (flag) {
        if (cz[a]) return 0;
        cz[a] = true;
        for (int i = 1; i <= M; ++i) {
            if (x[a][i]) dfs(i, N, M, false);
        }
    } else {
        if (cz[a + N]) return 0;
        cz[a + N] = true;
        dfs(l[a], N, M, true);
    }
    return 0;
}

int main() {
    cin >> N >> D;
    for (int i = 1; i <= N; ++i) cin >> X[i] >> Y[i];
    if (N == 1) {
        cout << 1 << endl << 1 << endl;
        return 0;
    }

    int ans = 1;
    vector<int> ansT;
    ansT.push_back(1);

    for (int i = 1; i < N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (dist(i, j) > D * D) continue;
            vector<int> A, B, C;
            for (int k = 1; k <= N; ++k) {
                if (k == i || k == j) continue;
                int T = getside(k, i, j);
                if (T == -1) A.push_back(k);
                if (T == 0) C.push_back(k);
                if (T == 1) B.push_back(k);
            }
            for (int p = 0; p < A.size(); ++p) {
                for (int q = 0; q < B.size(); ++q) {
                    if (dist(A[p], B[q]) > dist(i, j)) 
                        x[p + 1][q + 1] = 1; 
                    else
                        x[p + 1][q + 1] = 0;
                }
            }

            int R = A.size(), S = B.size();
            memset(l, 0, sizeof(l));
            for (int p = 1; p <= R; ++p) {
                memset(z, 0, sizeof(z));
                find(p, S);
            }

            int temp = 0;
            memset(z, 0, sizeof(z));
            for (int p = 1; p <= S; ++p) {
                temp += (l[p] > 0);
                z[l[p]] = true;
            }
            ans = max(ans, 2 + R + S + (int)C.size() - temp);
            
            if (ans > ansT.size()) {
                ansT = C;
                ansT.push_back(i);
                ansT.push_back(j);
                memset(cz, 0, sizeof(cz));
                for (int p = 1; p <= A.size(); ++p) {
                    if (z[p] || cz[p]) continue;
                    dfs(p, R, S, true);
                }
                for (int p = 1; p <= A.size(); ++p) {
                    if (cz[p] || check(p, R, S, true)) ansT.push_back(A[p - 1]);
                }
                for (int p = 1; p <= B.size(); ++p) {
                    if (!cz[R + p] || check(p, R, S, false)) ansT.push_back(B[p - 1]);
                }
            }
            
        }
    }
    cout << ans << endl;
    for (int i = 0; i < ansT.size(); ++i) cout << ansT[i] << " ";
    cout << endl;

    return 0;
}
