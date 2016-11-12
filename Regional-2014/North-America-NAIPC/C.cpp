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


const long long INF = 1LL * 1000000000 * 1000000000;
int N, M, T = 0;
int x[2020][2020], y[2020][2020];


long long getans() {
    long long ans = INF;
    bool flag = true;
    
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         x[i][j] = y[i][j];
         if (x[i][j] != 0) continue;
         x[i][j] = max(x[i][j - 1] + 1, x[i - 1][j] + 2);
     }
    
    long long temp = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         if (x[i][j] <= x[i - 1][j]) flag = false;
         if (x[i][j] <= x[i][j - 1]) flag = false;
         if (i > 1 && (x[i][j] + x[i - 1][j]) % 2 == 1) flag = false;
         if (j > 1 && (x[i][j] + x[i][j - 1]) % 2 == 0) flag = false;
         temp += x[i][j];
     }
     
    if (flag) ans = min(ans, temp);
    
    
    flag = true;
    temp = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         x[i][j] = y[i][j];
         if (x[i][j] != 0) continue;
         x[i][j] = max(x[i][j - 1] + 2, x[i - 1][j] + 1);
     }
    
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         if (x[i][j] <= x[i - 1][j]) flag = false;
         if (x[i][j] <= x[i][j - 1]) flag = false;
         if (i > 1 && (x[i][j] + x[i - 1][j]) % 2 == 0) flag = false;
         if (j > 1 && (x[i][j] + x[i][j - 1]) % 2 == 1) flag = false;
         temp += x[i][j];
     }
    
    if (flag) ans = min(ans, temp);
    return ans;
}


int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) scanf("%d", &y[i][j]);
    
    if (N == 1) {
        long long ans = 0;
        bool flag = true;
        for (int i = 1; i <= M; ++i) {
            if (y[1][i] != 0 && y[1][i] <= y[1][i - 1]) flag = false;
            if (y[1][i] == 0) y[1][i] = y[1][i - 1] + 1;
            ans += y[1][i];
        }
        if (flag) cout << ans << endl; else cout << -1 << endl;
        return 0;
    }
    
    if (M == 1) {
        long long ans = 0;
        bool flag = true;
        for (int i = 1; i <= N; ++i) {
            if (y[i][1] != 0 && y[i][1] <= y[i - 1][1]) flag = false;
            if (y[i][1] == 0) y[i][1] = y[i - 1][1] + 1;
            ans += y[i][1]; 
        }
        if (flag) cout << ans << endl; else cout << -1 << endl;
        return 0;
    }
    
    if (y[1][1] == 0) {
        long long ans = INF;
        y[1][1] = 1;
        ans = min(ans, getans());
        y[1][1] = 2;
        ans = min(ans, getans());
        
        if (ans == INF) cout << -1 << endl; else cout << ans << endl;
        return 0;
    }
    
    long long ans = 0;
    ans = getans();
    if (ans == INF) cout << -1 << endl; else cout << ans << endl;
    
    return 0;
}
