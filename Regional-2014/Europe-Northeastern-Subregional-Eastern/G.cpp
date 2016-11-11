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

const long long p = 1000000007;
long long f[2][303][2];

int main() {
    int n, a, b;
    int ind = 0, nind = 1;
    
    cin >> n >> a >> b;
    f[ind][1][0] = 1;
    f[ind][1][1] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < a; ++j) {
            f[nind][j+1][0] = f[ind][j][0];
            f[nind][1][1] = (f[nind][1][1] + f[ind][j][0]) % p;
        }
        f[nind][1][1] = (f[nind][1][1] + f[ind][a][0]) % p;
        for (int j = 1; j < b; ++j) {
            f[nind][j+1][1] = f[ind][j][1];
            f[nind][1][0] = (f[nind][1][0] + f[ind][j][1]) % p;
        }
        f[nind][1][0] = (f[nind][1][0] + f[ind][b][1]) % p;
        ind = nind;
        nind = 1 - ind;
        f[nind][1][0] = 0;
        f[nind][1][1] = 0;
    }
    
    long long res = 0;
    for (int i = 1; i <= a; ++i) res = (res + f[ind][i][0]) % p;
    for (int i = 1; i <= b; ++i) res = (res + f[ind][i][1]) % p;
    
    cout << res << endl;

    return 0;
}
