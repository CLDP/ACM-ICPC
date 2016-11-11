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

int m[200005];
int r[200005];
int f[200005][2];
int from[200005][2];

int main() {
    int n, cnt = 0;
    
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &m[i], &r[i]);
        if (m[i] <= r[i]) ++cnt;
    }
    int win = n - cnt;
    
    if (win == 0) {
        cout << -1 << endl;
        return 0;
    }
    
    if (cnt < win) {
        cout << 0 << endl;
        return 0;
    }
    
    cnt = cnt - (win - 1);
    f[0][0] = 1000000;
    f[0][1] = cnt;
    for (int i = 1; i < n; ++i) {
        if (f[i - 1][0] < f[i - 1][1]) {
            f[i][1] = f[i - 1][0];
            from[i][1] = 0;
        } else {
            f[i][1] = f[i-1][1];
            from[i][1] = 1;
        }
        f[i][0] = 1000000;
        if (f[i][1] == 0) continue;
        if (((m[i] + m[i - 1] > r[i] + r[i - 1])
         && ((m[i] <= r[i]) || (m[i - 1] <= r[i - 1]))) 
         || ((m[i] <= r[i]) && (m[i - 1] <= r[i - 1]))) {
            f[i][0] = f[i - 1][1] - 1;
            from[i][0] = 1;
        }
    }
    
    int st;
    if (f[n - 1][1] == 0) st = 1;
    else 
    if (f[n - 1][0] == 0) st = 0;
    else {
        cout << -1 << endl;
        return 0;
    }
    
    cout << cnt << endl;
    for (int i = n - 1; i > 0; --i) {
        if (st == 0) {
            cout << i << " " << i + 1 << endl;
            st = 1;
        } else
            st = from[i][1];
    }

    return 0;
}
