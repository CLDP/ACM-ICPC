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

long double f[65][41][9];
double fac[10];

long double solve(int a, int b, int c) {
    if (f[a][b][c] != -1)
        return f[a][b][c];
    if (((c == 0) || (a == 63)) && (b != 0)) {
        f[a][b][c] = 0;
        return f[a][b][c];
    }
    
    vector<int> pos;
    for (int i = 1, j = 0; i < 64; i *= 2, ++j)
        if ((a & i) == 0) pos.push_back(j);
    
    if (min(5, pos.back() + 1) * c < b) {
        f[a][b][c] = 0;
        return f[a][b][c];
    }
    
    vector<int> v(c + 1, 0);
    f[a][b][c] = 0;
    double totp = 0;
    while (v[c] == 0) {
        vector<int> cnt(6, 0);
        double p = fac[c];
        for (int i = 0; i < c; ++i) {
            cnt[v[i]]++;
            p = p / 6;
        }
        for (int i = 0; i < 6; ++i) p = p / fac[cnt[i]];
        totp += p;
        long double best = 0;
        for (int i = 0; i < pos.size(); ++i) {
            if (cnt[pos[i]] > 0) {
                if ((cnt[pos[i]] * min(5, pos[i] + 1) >= b) && ((a >= 32) || (pos[i] == 5)))
                    best = 1;
                else
                    best = max(best, solve(a | (1 << pos[i]), max(0, b - cnt[pos[i]] * min(5, pos[i] + 1)), c - cnt[pos[i]]));
            }
        }
        f[a][b][c] += p * best;
        
        v[0]++;
        int ind = 0;
        while (v[ind] == 6)
            v[++ind]++;
        while (ind > 0)
        {
            v[ind-1] = v[ind];
            ind--;
        }
    }
    return f[a][b][c];
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < 10; ++i)
        fac[i] = fac[i-1] * i;
    for (int i = 0; i < 65; ++i)
        for (int j = 0; j < 41; ++j)
            for (int k = 0; k < 9; ++k)
                f[i][j][k] = -1;
    
    for (int i = 1; i <= 40; ++i) solve(0, i, 8);
    
    int n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        double res = f[0][n][8];
        printf("%.12lf\n", res);
    }

    return 0;
}
