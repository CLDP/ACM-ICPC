#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int G, B, S;
vector<int> x[30];
int f[1 << 21][2], ff[1 << 21], gg[1 << 21][10];
bool z[1 << 21][2];

int dp(int a, bool b) {
    if (z[a][b]) return f[a][b];
    z[a][b] = true;
    if (a == (1 << B) - 1) return f[a][b] = 0;
    f[a][b] = -INF;
    
    for (int i = 0; i < B; ++i) {
        if (a & (1 << i)) continue;
        int temp = ff[a | (1 << i)] - ff[a];
        if (temp > 0) 
            f[a][b] = max(f[a][b], temp + dp(a | (1 << i), b)); 
        else
            f[a][b] = max(f[a][b], temp - dp(a | (1 << i), !b));
    }
    
    return f[a][b];
}

int main() {
    while (cin >> G >> B >> S) {
        if (G + B + S == 0) break;
        for (int i = 0; i < B; ++i) {
            int n;
            cin >> n;
            x[i] = vector<int> (n);
            for (int j = 0; j < n; ++j) cin >> x[i][j];
        }
        memset(gg, 0, sizeof(gg));
        ff[0] = 0;
        for (int i = 1; i < (1 << B); ++i) {
            int j;
            for (j = 0; j < B; ++j)
             if (i & (1 << j)) break;
            
            int p = i - (1 << j);
            for (int k = 1; k <= G; ++k) gg[i][k] = gg[p][k];
            for (int k = 0; k < x[j].size(); ++k) ++gg[i][x[j][k]];
            ff[i] = 0;
            for (int j = 1; j <= G; ++j) ff[i] += gg[i][j] / S;
        }
        
        memset(z, 0, sizeof(z));
        cout << dp(0, 0) << endl;
    }
    return 0;
}
