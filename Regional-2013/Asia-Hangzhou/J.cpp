#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const int INF = 1000000007;

int Comb[MAXN][MAXN], CombS[MAXN][MAXN];
int fact[MAXN];
int B[MAXN][MAXN];
 
int get(int R, int C, int P) {
    return Comb[R][P] * (long long) B[C][P] % INF;
}
 
int getCombS(int k, int mi, int ma) {
    if (mi == 0) return CombS[k][ma];
    return (CombS[k][ma] - CombS[k][mi - 1]) % INF;
}


int main() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) fact[i] = fact[i - 1] * (long long) i % INF;
    for (int i = 0; i < MAXN; ++i) {
        Comb[i][0] = 1;
        CombS[i][0] = 1;
        for (int j = 1; j < i + 1; ++j) Comb[i][j] = (Comb[i - 1][j] + Comb[i - 1][j - 1]) % INF;
        for (int j = 1; j < MAXN; ++j) CombS[i][j] = (CombS[i][j - 1] + Comb[i][j]) % INF;
    }
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (i - 2 * j < 0) break;
            B[i][j] = 1;
            int ni = i;
            for (int k = 0; k < j; ++k) {
                B[i][j] = B[i][j] * (long long) Comb[ni][2] % INF;
                ni -= 2;
            }
        }
    }
 
    int times;
    cin >> times;
    while (times--) {
        int N, M, P, Q;
        cin >> N >> M >> P >> Q;
        int ans = 0;
        for (int i = 0; i <= P; ++i)
         for (int j = 0; j <= P; ++j) {
             if (2 * i + 2 * j > P) break;
             int tmp = get(N, M, i) * (long long) get(M - 2 * i, N - i, j) % INF;
             int nN = N - i - 2 * j, nM = M - j - 2 * i;
             int nP = P - 2 * i - 2 * j, nQ = Q;
             for (int k = 0; k <= P + Q; ++k) {
                 if (k > nP + nQ) break;
                 int miP = max(0, k - nQ);
                 int maP = min(k, nP);
                 int tmp2 = getCombS(k, miP, maP) * (long long) Comb[nN][k] % INF 
                          * Comb[nM][k] % INF * fact[k] % INF;
                 ans = (ans + tmp * (long long) tmp2) % INF;
             }
         }
        ans = ((ans - 1) % INF + INF) % INF;
        cout << ans << endl;
    }
    return 0;
}
