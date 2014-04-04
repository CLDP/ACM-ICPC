#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

bool x[6][31][31];
bool z[31][31][31];
char y[31][31][31];

struct node {
    int a, b, c;
};

int n;

bool check(int a, int b, int c) {
    if (!x[0][n-1-c][n-1-a]) return false;
    if (!x[1][n-1-c][b]) return false;
    if (!x[2][n-1-c][a]) return false;
    if (!x[3][n-1-c][n-1-b]) return false;
    if (!x[4][n-1-b][n-1-a]) return false;
    if (!x[5][b][n-1-a]) return false;
    return true;
}

int main() {
    string p;
    while (cin >> n) {
        if (n == 0) break;
        getline(cin, p);
        for (int k = 0; k < 6; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    char c;
                    cin.get(c);
                    if (c == 'X') x[k][i][j] = false; else x[k][i][j] = true;
                }
                getline(cin, p);
            }
        }
        
        node p;
        p.a = p.b = p.c = 1;
        memset(z, 0, sizeof(z));
        
        z[1][1][1] = true;
        queue<node> que;
        que.push(p);
        
        while (!que.empty()) {
            p = que.front();
            if (p.a == n-2 && p.b == n-2 && p.c == n-2) break;
            que.pop();
            if (p.b > 0 && !z[p.a][p.b-1][p.c] && check(p.a, p.b-1, p.c)) {
                y[p.a][p.b-1][p.c] = 'F';
                z[p.a][p.b-1][p.c] = true;
                --p.b;
                que.push(p);
                ++p.b;
            } 
            if (p.b < n-1 && !z[p.a][p.b+1][p.c] && check(p.a, p.b+1, p.c)) {
                y[p.a][p.b+1][p.c] = 'B';
                z[p.a][p.b+1][p.c] = true;
                ++p.b;
                que.push(p);
                --p.b;
            } 
            if (p.a < n-1 && !z[p.a+1][p.b][p.c] && check(p.a+1, p.b, p.c)) {
                y[p.a+1][p.b][p.c] = 'L';
                z[p.a+1][p.b][p.c] = true;
                ++p.a;
                que.push(p);
                --p.a;
            } 
            if (p.a > 0 && !z[p.a-1][p.b][p.c] && check(p.a-1, p.b, p.c)) {
                y[p.a-1][p.b][p.c] = 'R';
                z[p.a-1][p.b][p.c] = true;
                --p.a;
                que.push(p);
                ++p.a;
            } 
            if (p.c < n-1 && !z[p.a][p.b][p.c+1] && check(p.a, p.b, p.c+1)) {
                y[p.a][p.b][p.c+1] = 'U';
                z[p.a][p.b][p.c+1] = true;
                ++p.c;
                que.push(p);
                --p.c;
            } 
            if (p.c > 0 && !z[p.a][p.b][p.c-1] && check(p.a, p.b, p.c-1)) {
                y[p.a][p.b][p.c-1] = 'D';
                z[p.a][p.b][p.c-1] = true;
                --p.c;
                que.push(p);
                ++p.c;
            } 
        }
        
        string ans;
        while (p.a != 1 || p.b != 1 || p.c != 1) {
            ans = y[p.a][p.b][p.c] + ans;
            switch (y[p.a][p.b][p.c]) {
                case 'R' : ++p.a; break;
                case 'L' : --p.a; break;
                case 'U' : --p.c; break;
                case 'D' : ++p.c; break;
                case 'F' : ++p.b; break;
                case 'B' : --p.b; break;
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}
