#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 205;

bool x[MAXN][MAXN];
int U[MAXN][MAXN], R[MAXN][MAXN], F[MAXN][MAXN], FU[MAXN][MAXN][MAXN], FR[MAXN][MAXN][MAXN];
int CNT[MAXN][MAXN];

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int cal(int A, int B) {
    int ans = 0;
    for (int i = 1; i <= B; ++i)
     if (gcd(A, i) == 1) ++ans;
    return ans;
}

int main() {
    for (int i = 1; i <= 200; ++i)
     for (int j = 1; j <= 200; ++j) CNT[i][j] = cal(i, j) + CNT[i - 1][j];
    
    int T;
    scanf("%d", &T);
    for (int times = 1; times <= T; ++times) {
        int N, a, b;
        scanf("%d", &N);
        memset(x, 0, sizeof(x));
        int A = 0, B = 0;
        vector<pair<int, int> > XX;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &a, &b);
            x[a][b] = true;
            XX.push_back(make_pair(a, b));
            A = max(A, a);
            B = max(B, b);
        }
        
        
        
        for (int i = 1; i <= A + 1; ++i)
         for (int j = 1; j <= B + 1; ++j) {
             U[i][j] = R[i][j] = F[i][j] = 0;
             for (int k = 1; k <= A + 1; ++k) FR[i][j][k] = 0;
             for (int k = 1; k <= B + 1; ++k) FU[i][j][k] = 0;
         }
        
        for (int j = B; j >= 1; --j)
         for (int i = A; i >= 1; --i) {
             F[i][j] = F[i + 1][j] + F[i][j + 1] - F[i + 1][j + 1];
             if (!x[i][j]) {
                 U[i][j] = R[i][j] = 0;
                 continue;
             }
             U[i][j] = U[i][j + 1] + 1;
             R[i][j] = R[i + 1][j] + 1;
             F[i][j] += CNT[U[i][j] - 1][R[i][j] - 1];
         }
        
        int temp = A;
        for (A = 1; A <= temp; ++A) {
            for (int i = 1; i <= A + 1; ++i)
             for (int j = 1; j <= B + 1; ++j) U[i][j] = R[i][j] = 0;
             
            for (int j = B; j >= 1; --j)
             for (int i = A; i >= 1; --i) {
                 FR[i][j][A] = FR[i + 1][j][A] + FR[i][j + 1][A] - FR[i + 1][j + 1][A];
                 if (!x[i][j]) {
                     U[i][j] = R[i][j] = 0;
                     continue;
                 }
                 U[i][j] = U[i][j + 1] + 1;
                 R[i][j] = R[i + 1][j] + 1;
                 FR[i][j][A] += CNT[U[i][j] - 1][R[i][j] - 1];
             }
        }
        A = temp;
        temp = B;
        for (B = 1; B <= temp; ++B) {
            for (int i = 1; i <= A + 1; ++i)
             for (int j = 1; j <= B + 1; ++j) U[i][j] = R[i][j] = 0;
             
            for (int j = B; j >= 1; --j)
             for (int i = A; i >= 1; --i) {
                 FU[i][j][B] = FU[i + 1][j][B] + FU[i][j + 1][B] - FU[i + 1][j + 1][B];
                 if (!x[i][j]) {
                     U[i][j] = R[i][j] = 0;
                     continue;
                 }
                 U[i][j] = U[i][j + 1] + 1;
                 R[i][j] = R[i + 1][j] + 1;
                 FU[i][j][B] += CNT[U[i][j] - 1][R[i][j] - 1];
             }
        }
        B = temp;
         
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            int a = XX[i].first, b = XX[i].second;
            ans += 1LL * F[a + 1][b + 1] * CNT[U[a][b] - 1][R[a][b] - 1] * 2;
            for (int j = 1; j < U[a][b]; ++j) {
                ans += 1LL * (F[1][b + j + 1] - F[a + 1][b + j + 1] - FR[1][b + j + 1][a - 1]) * (CNT[j][R[a][b] - 1] - CNT[j - 1][R[a][b] - 1]) * 2;
                ans += 1LL * FR[1][b + j + 1][a - 1] * (CNT[j][R[a][b] - 1] - CNT[j - 1][R[a][b] - 1]);
            }
            for (int j = 1; j < R[a][b]; ++j) {
                ans += 1LL * (F[a + j + 1][1] - F[a + j + 1][b + 1] - FU[a + j + 1][1][b - 1]) * (CNT[U[a][b] - 1][j] - CNT[U[a][b] - 1][j - 1]) * 2;
                ans += 1LL * FU[a + j + 1][1][b - 1] * (CNT[U[a][b] - 1][j] - CNT[U[a][b] - 1][j - 1]);
            }
        }
        
        printf("Case #%d: %I64d\n", times, ans);
    }
    return 0;
}
