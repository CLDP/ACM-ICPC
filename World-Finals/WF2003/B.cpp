#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

bool x[400], y[400];
int f[400][4];
string g[400][4];

int deal(int &L, bool x[], const string &P) {
    int xx[110], LP = P.size();
    for (int i = 0; i < LP; ++i) xx[LP - i] = P[i] - '0';
    L = 0;
    while (LP > 0) {
        x[++L] = xx[1] % 2;
        for (int i = LP; i >= 1; --i) {
            xx[i - 1] += xx[i] % 2 * 10;
            xx[i] /= 2;
        }
        if (xx[LP] == 0) --LP;
    }
    return 0;
}


int dp(int i, int j) {
    if (i == 0 || j / 2 != y[i]) {
        // should touch
        int b = (1 - j % 2) * 2 + (1 - x[i + 2]);
        string temp = g[i][j] + "1";
        if (f[i + 1][b] > f[i][j] + 1) {
            f[i + 1][b] = f[i][j] + 1;
            g[i + 1][b] = temp;
        } else 
        if (f[i + 1][b] == f[i][j] + 1) {
            if (temp < g[i + 1][b]) g[i + 1][b] = temp;
        }
    }
    if (i == 0 || j / 2 == y[i]) {
        // should not touch
        int b = j % 2 * 2 + x[i + 2];
        string temp = g[i][j] + "0";
        if (f[i + 1][b] > f[i][j]) {
            f[i + 1][b] = f[i][j];
            g[i + 1][b] = temp;
        } else 
        if (f[i + 1][b] == f[i][j]) {
            if (temp < g[i + 1][b]) g[i + 1][b] = temp;
        }
    }
    return 0;
}


int main() {
    int times = 0;
    string P, Q;
    bool first = true;
    while (cin >> P >> Q) {
        if (P[0] == '0' && Q[0] == '0') break;
        if (!first) cout << endl;
        first = false;
        
        int LA = 0, LB = 0;
        deal(LA, x, P);
        deal(LB, y, Q);
        
        int N = max(LA, LB);
        
        for (int i = LA + 1; i <= N; ++i) x[i] = 0;
        for (int i = LB + 1; i <= N; ++i) y[i] = 0;
        
        for (int i = 1; i <= N / 2; ++i) {
            swap(x[i], x[N + 1 - i]);
            swap(y[i], y[N + 1 - i]);
        }
        
        for (int i = 0; i <= N; ++i)
         for (int j = 0; j < 4; ++j) {
             f[i][j] = INF;
             g[i][j] = "";
         }
        
        if (x[1]) {
            f[0][1] = f[0][3] = 0;
        } else {
            f[0][0] = f[0][2] = 0;
        }
        
        x[N + 1] = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (f[i][j] == INF) continue;
                dp(i, j);
            }
        }
        
        int ans = f[N][y[N] * 2];
        string ansT = g[N][y[N] * 2];
        if (f[N][y[N] * 2 + 1] < ans || (f[N][y[N] * 2 + 1] == ans && g[N][y[N] * 2 + 1] < ansT)) {
            ans = f[N][y[N] * 2 + 1];
            ansT = g[N][y[N] * 2 + 1];
        }
        
        cout << "Case Number " << ++times << ": ";
        if (ans == INF) {
            cout << "impossible" << endl;
            continue;
        }
        
        int res[110], L = 1;
        memset(res, 0, sizeof(res));
        res[1] = 0;
        for (int j = 0; j < N; ++j) {
            for (int i = L; i >= 1; --i) {
                res[i] += res[i];
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
            if (res[L + 1] > 0) ++L;
            
            if (ansT[j] == '1') ++res[1];
        }
        
        for (int i = L; i >= 1; --i) cout << res[i];
        cout << endl;
    }

    return 0;
}
