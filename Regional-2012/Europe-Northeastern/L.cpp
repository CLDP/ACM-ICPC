#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1510;
const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};


int N, M;
int x[MAXN][MAXN], y[MAXN][MAXN];
int B[MAXN][MAXN], C[MAXN][MAXN], CA[MAXN][MAXN], CB[MAXN][MAXN], UA[MAXN][MAXN], UB[MAXN][MAXN];

int dfsL(int a, int b, int d) {
    if (a == 0 && b == 0) return 0;
    d = (d + 3) % 4;
    x[a][b] = 1;
    for (int i = 0; i < 4; ++i) {
        int p = a + MX[(d + i) % 4], q = b + MY[(d + i) % 4];
        if (0 <= p && p < N && 0 <= q && q < M && x[p][q] != -1) {
            dfsL(p, q, (d + i) % 4);
            return 0;
        }
    }
    return 0;
}

int dfsR(int a, int b, int d) {
    if (a == 0 && b == 0) return 0;
    d = (d + 1) % 4;
    y[a][b] = 1;
    for (int i = 0; i < 4; ++i) {
        int p = a + MX[(d + 4 - i) % 4], q = b + MY[(d + 4 - i) % 4];
        if (0 <= p && p < N && 0 <= q && q < M && y[p][q] != -1) {
            dfsR(p, q, (d + 4 - i) % 4);
            return 0;
        }
    }
    return 0;
}

bool check(int a, int b, int R) {
    int p = a + R, q = b + R;
    int A = CA[p + 1][q + 1] - CA[p + 1][b] - CA[a][q + 1] + CA[a][b];
    int B = CB[p + 1][q + 1] - CB[p + 1][b] - CB[a][q + 1] + CB[a][b];
    return A > 0 && B > 0;
}


int main() {
    cin >> M >> N;
    for (int i = 0; i < N; ++i) {
        string P;
        cin >> P;
        for (int j = 0; j < M; ++j) {
            if (P[j] == '.') 
                x[i][j] = y[i][j] = C[i][j] = 0; 
            else 
                x[i][j] = y[i][j] = C[i][j] = -1;
        }
    }
    dfsL(N - 1, M - 1, 3);
    dfsR(N - 1, M - 1, 0);
    for (int i = 1; i <= N; ++i) 
     for (int j = 1; j <= M; ++j) {
         if (x[i - 1][j - 1] == -1) continue;
         B[i][j] = min(B[i - 1][j - 1], min(B[i][j - 1], B[i - 1][j])) + 1;
     }
     
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (x[i][j] == -1) x[i][j] = 0;
            if (y[i][j] == -1) y[i][j] = 0;
        }
    }
    B[N][M] = 0;
    x[N - 1][M - 1] = x[0][0] = y[N - 1][M - 1] = y[0][0] = 0;
    
    for (int j = 0; j < M; ++j) {
        for (int i = 0; i < N; ++i) {
            UA[i + 1][j + 1] = UA[i][j + 1] + x[i][j];
            CA[i + 1][j + 1] = UA[i + 1][j + 1] + CA[i + 1][j];
            UB[i + 1][j + 1] = UB[i][j + 1] + y[i][j];
            CB[i + 1][j + 1] = UB[i + 1][j + 1] + CB[i + 1][j];
        }
    }
    
    C[0][0] = C[N - 1][M - 1] = -1;
    
    int ans = 10000, ax, ay;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (C[i][j] == -1) continue;
            if (x[i][j] == 1 && y[i][j] == 1) {
                ans = 1, ax = i, ay = j;
                continue;
            }
            int L = 0, R = min(N - 1 - i, M - 1 - j);
            if (R == 0 || !check(i, j, R)) continue;
            while (L + 1 < R) {
                int mid = (L + R) >> 1;
                if (check(i, j, mid)) R = mid; else L = mid;
            }
            if (B[i + R + 1][j + R + 1] > R && R + 1 < ans) {
                ans = R + 1, ax = i, ay = j;
                continue;
            }
        }
    }
    
    if (ans == 10000) {
        cout << "Impossible" << endl;
    } else {
        cout << ans << " " << ay + 1 << " " << ax + 1 << endl;
    }
    return 0;
}
