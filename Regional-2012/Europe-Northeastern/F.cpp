#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};

char x[20][20];
char z[3][3][3];

char next(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c - 'a' + 'A' + 1;
}

bool check(int a, int b, char c) {
    return 0 <= a && a < 15 && 0 <= b && b < 15 && x[a][b] == c;
}

bool dfs(int t, int sx, int sy, int sd, int a, int b, int c, int ma, int mb, int mc) {
    if (a < 0 || a > 2 || b < 0 || b > 2 || c < 0 || c > 2) return false;
    if (z[a][b][c]) return false;
    z[a][b][c] = x[sx][sy];
    if (t == 26) return true;
    char nc = next(x[sx][sy]);
    int p = sx + MX[sd], q = sy + MY[sd];
    if (check(p, q, nc)) {
        if (dfs(t + 1, p, q, sd, a + ma, b + mb, c + mc, ma, mb, mc)) return true;
        z[a][b][c] = 0;
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        if (i == sd) continue;
        p = sx + MX[i], q = sy + MY[i];
        if (check(p, q, nc)) {
            if (ma == 0) {
                if (dfs(t + 1, p, q, i, a + 1, b, c, 1, 0, 0)) return true;
                if (dfs(t + 1, p, q, i, a - 1, b, c, -1, 0, 0)) return true;
            }
            if (mb == 0) {
                if (dfs(t + 1, p, q, i, a, b + 1, c, 0, 1, 0)) return true;
                if (dfs(t + 1, p, q, i, a, b - 1, c, 0, -1, 0)) return true;
            }
            if (mc == 0) {
                if (dfs(t + 1, p, q, i, a, b, c + 1, 0, 0, 1)) return true;
                if (dfs(t + 1, p, q, i, a, b, c - 1, 0, 0, -1)) return true;
            }
        }
    }
    z[a][b][c] = 0;
    return false;
}

int main() {
    int sx, sy, sd;
    for (int i = 0; i < 15; ++i) {
        cin >> x[i];
        for (int j = 0; j < 15; ++j) 
         if (x[i][j] == 'A') sx = i, sy = j;
    }
    for (int i = 0; i < 4; ++i) {
        int a = sx + MX[i], b = sy + MY[i];
        if (0 <= a && a < 15 && 0 <= b && b < 15 && x[a][b] == 'a') {
            sd = i;
            break;
        }
    }
    bool flag = false;
    if (!flag) flag = dfs(0, sx, sy, sd, 0, 0, 0, 1, 0, 0);
    if (!flag) flag = dfs(0, sx, sy, sd, 1, 0, 0, 1, 0, 0);
    if (!flag) flag = dfs(0, sx, sy, sd, 1, 0, 0, 0, 1, 0);
    if (!flag) flag = dfs(0, sx, sy, sd, 1, 1, 0, 0, 1, 0);
    if (!flag) flag = dfs(0, sx, sy, sd, 1, 1, 0, 0, 0, 1);
    if (!flag) flag = dfs(0, sx, sy, sd, 1, 1, 1, 1, 0, 0);
    
    for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) cout << z[0][j][k];
        cout << " ";
        for (int k = 0; k < 3; ++k) cout << z[1][j][k];
        cout << " ";
        for (int k = 0; k < 3; ++k) cout << z[2][j][k];
        cout << endl;
    }
    cout << endl;
    
    return 0;
}
