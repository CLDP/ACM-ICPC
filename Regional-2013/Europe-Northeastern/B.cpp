#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

long double f[2][3005][2];
long double win[2];

int main() {
    freopen("bonus.in", "r", stdin);
    freopen("bonus.out", "w", stdout);

    long long a, b, n;
    
    cin >> n >> a >> b;
    if (a + b < n) {
        cout << 1 << endl << 1 << endl;
        return 0;
    }
    
    f[0][0][0] = 1.0;
    f[0][0][1] = 1.0;
    for (long long i = 0; i < n; ++i) {
        int ind = i % 2;
        for (long long j = 0; j <= min(a, i); ++j) {
            if (j < a) {
                f[ind^1][j+1][0] += 
                    f[ind][j][0] * ((long double)(2 * (a - j))) / (2 * (a - j) + b - i + j + 2);
                f[ind^1][j+1][1] += 
                    f[ind][j][1] * ((long double)(2 * (a - j))) / (2 * (a - j) + b - i + j + 1);
            }
            if (i - j < b) {
                f[ind^1][j][0] += 
                    f[ind][j][0] * ((long double)(b - i + j)) / (2 * (a - j) + b - i + j + 2);
                f[ind^1][j][1] += 
                    f[ind][j][1] * ((long double)(b - i + j)) / (2 * (a - j) + b - i + j + 1);
            }
            if (i - j <= b) {
                win[0] += f[ind][j][0] * ((long double)(2)) / (2 * (a - j) + b - i + j + 2);
                win[1] += f[ind][j][1] * ((long double)(1)) / (2 * (a - j) + b - i + j + 1);
            }
            f[ind][j][0] = 0;
            f[ind][j][1] = 0;
        }
    }
    
    cout.precision(12);
    cout << win[0] << endl << win[1] << endl;
    
    return 0;
}
