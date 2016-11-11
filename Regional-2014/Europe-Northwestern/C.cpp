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

const int INF = 1000000000;

int x[2010];
int f[2010][22];

int ROUND(int a) {
    if (a % 10 < 5) return (a / 10) * 10; else return (a / 10 + 1) * 10;
}

int main() {
    int N, D;
    cin >> N >> D;
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i <= N; ++i)
     for (int j = 0; j <= D; ++j) f[i][j] = INF;
     
    for (int i = 0; i < N; ++i)
     for (int j = 0; j <= min(i, D); ++j) {
         if (j == 0) {
             f[i][j] = 0;
             for (int k = 0; k <= i; ++k) f[i][j] += x[k];
             f[i][j] = ROUND(f[i][j]);
             continue;
         }
         int temp = x[i];
         for (int k = i - 1; k >= 0; --k) {
             f[i][j] = min(f[i][j], f[k][j - 1] + ROUND(temp));
             temp += x[k];
         }
     }
    
    int ans = INF;
    for (int i = 0; i <= D; ++i) ans = min(ans, f[N - 1][i]);
    cout << ans << endl;
    return 0;
}
