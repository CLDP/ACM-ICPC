#include <string>
#include <cmath>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 510;
const int INF = 1000000007;
const double EPS = 1e-8;
const double SHIFT = EPS * 10;

const int OPTIMAL = -1;
const int UNBOUNDED = -2;
const int FEASIBLE = -3;
const int INFEASIBLE = -4;
const int PIVOT_OK = 1;

int basic[MAXN], row[MAXN], col[MAXN];
double C0[MAXN], A[MAXN][MAXN], R[MAXN], X[MAXN];

int dcmp(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

int Pivot(int N, int M, double *C, int &i, int &j) {
    int k = -1;
    for (j = 0; j <= N; ++j)
        if (!basic[j] && dcmp(C[j]) > 0)
            if (k < 0 || dcmp(C[j] - C[k]) > 0) k = j;
    j = k;
    if (k < 0) return OPTIMAL;
    double mins = INF;
    k = -1;
    for (i = 1; i <= M; ++i)
     if (dcmp(A[i][j]) > 0)
      if (dcmp(R[i] / A[i][j] - mins) < 0) {
          mins = R[i] / A[i][j];
          k = i;
      }
    i = k;
    if (k < 0) return UNBOUNDED;
    return PIVOT_OK;
}

int PhaseII(int N, int M, double *C, double &ans, int PivotIndex) {
    int i, j, k;
    while (k = Pivot(N, M, C, i, j), k == PIVOT_OK || PivotIndex) {
        if (PivotIndex) {
            j = 0;
            i = PivotIndex;
            PivotIndex = 0;
        }
        basic[row[i]] = 0;
        col[row[i]] = 0;
        basic[j] = 1;
        col[j] = i;
        row[i] = j;
        double temp = A[i][j];
        for (k = 0; k <= N; ++k) A[i][k] /= temp;
        R[i] /= temp;
        for (k = 1; k <= M; ++k) 
         if (k != i && dcmp(A[k][j])) {
             temp = -A[k][j];
             for (int l = 0; l <= N; ++l) A[k][l] += temp * A[i][l];
             R[k] += temp * R[i];
         }
        temp = -C[j];
        for (int l = 0; l <= N; ++l) C[l] += A[i][l] * temp;
        ans -= temp * R[i];
    }
    return k;
}

int PhaseI(int N, int M, double *C, double &ans) {
    int k = -1;
    double minr = 0;
    for (int i = 1; i <= M; ++i) 
     if (dcmp(R[i] - minr) < 0) {
         minr = R[i];
         k = i;
     }
    if (k < 0) return FEASIBLE;
    for (int i = 1; i <= M; ++i) A[i][0] = -1;
    for (int j = 1; j <= N; ++j) C0[j] = 0;
    C0[0] = -1;
    double ans0 = 0;
    PhaseII(N, M, C0, ans0, k);
    if (dcmp(ans0) < 0) return INFEASIBLE;
    for (int i = 1; i <= M; ++i) A[i][0] = 0;
    for (int j = 1; j <= N; ++j) 
     if (dcmp(C[j]) && basic[j]) {
         double temp = C[j];
         ans += R[col[j]] * temp;
         for (int i = 0; i <= N; ++i) C[i] -= temp * A[col[j]][i];
     }
    return FEASIBLE;
}

int simplex(int N, int M, double *C, double &ans) {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(basic, 0, sizeof(basic));
    memset(C0, 0, sizeof(C0));

    for (int i = 1; i <= M; ++i) {
        for (int j = N + 1; j <= N + M; ++j) A[i][j] = 0;
        A[i][N + i] = 1;
        A[i][0] = 0;
        row[i] = N + i;
        col[N + i] = i;
    }
    int k = PhaseI(N + M, M, C, ans);
    if (k == INFEASIBLE) return k;
    k = PhaseII(N + M, M, C, ans, 0);
    for (int j = 0; j <= N + M; ++j) X[j] = 0;
    for (int i = 1; i <= M; ++i) X[row[i]] = R[i];
    return k;
}

int n, m;
double ans, C[MAXN];


int main() {
    int N, cnt = 0;
    int X[33][33], Y[33][33], NX[33][33];
    vector<pair<int, int> > XX;
    cin >> N;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         cin >> X[i][j];
         if (X[i][j] > 0) {
             NX[i][j] = ++cnt;
             XX.push_back(make_pair(i, j));
         }
         if (X[i][j] == -1) X[i][j] = INF;
         Y[i][j] = X[i][j];
     }

    for (int k = 0; k < N; ++k)
     for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
       if (X[i][k] + X[k][j] < X[i][j]) X[i][j] = X[i][k] + X[k][j];

    int RR, QQ;
    cin >> RR;
    vector<int> Z[MAXN];
    vector<int> ZZ;
    for (int T = 0; T < RR; ++T) {
        int s, d, t;
        cin >> s >> d >> t;
        ZZ.push_back(t);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (X[s][i] + Y[i][j] + X[j][d] == X[s][d]) {
                    Z[T].push_back(NX[i][j]);
                }
            }
        }
    }

    cin >> QQ;
    for (int T = 0; T < QQ; ++T) {
        int s, d;
        cin >> s >> d;
        if (s == d) {
            printf("%d %d 0 0\n", s, d);
            continue;
        }
        vector<int> S;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (X[s][i] + Y[i][j] + X[j][d] == X[s][d]) {
                    S.push_back(NX[i][j]);
                }
            }
        }

        n = cnt;
        m = cnt + cnt + RR + RR;

        memset(A, 0, sizeof(A));
        memset(R, 0, sizeof(R));
        for (int i = 1; i <= cnt; ++i) {
            int ss = XX[i - 1].first, tt = XX[i - 1].second;
            A[i][i] = 1;
            R[i] = 2 * Y[ss][tt];
            A[cnt + i][i] = -1;
            R[cnt + i] = -Y[ss][tt];
        }

        for (int i = 1; i <= RR; ++i) {
            for (int j = 0; j < Z[i - 1].size(); ++j) {
                int a = Z[i - 1][j];
                A[cnt + cnt + i][a] = 1;
                A[cnt + cnt + RR + i][a] = -1;
            }
            R[cnt + cnt + i] = ZZ[i - 1] + SHIFT;
            R[cnt + cnt + RR + i] = -ZZ[i - 1] + SHIFT;
        }

        memset(C, 0, sizeof(C));
        for (int i = 0; i < S.size(); ++i) C[S[i]] = -1;

        printf("%d %d", s, d);
        ans = 0;
        simplex(n, m, C, ans);
        printf(" %.9lf", -ans);

        memset(A, 0, sizeof(A));
        memset(R, 0, sizeof(R));
        for (int i = 1; i <= cnt; ++i) {
            int ss = XX[i - 1].first, tt = XX[i - 1].second;
            A[i][i] = 1;
            R[i] = 2 * Y[ss][tt];
            A[cnt + i][i] = -1;
            R[cnt + i] = -Y[ss][tt];
        }

        for (int i = 1; i <= RR; ++i) {
            for (int j = 0; j < Z[i - 1].size(); ++j) {
                int a = Z[i - 1][j];
                A[cnt + cnt + i][a] = 1;
                A[cnt + cnt + RR + i][a] = -1;
            }
            R[cnt + cnt + i] = ZZ[i - 1] + SHIFT;
            R[cnt + cnt + RR + i] = -ZZ[i - 1] + SHIFT;
        }

        memset(C, 0, sizeof(C));
        for (int i = 0; i < S.size(); ++i) C[S[i]] = 1;

        ans = 0;
        simplex(n, m, C, ans);
        printf(" %.9lf\n", ans);
    }

    return 0;
}
