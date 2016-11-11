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

int f[200005];
int l[200005];
int r[200005];

int main() {
    int n, k;
    
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> f[i];
    l[0] = f[0];
    for (int i = 1; i < n; ++i) {
        l[i] = l[i-1] + f[i];
        if (i >= k) l[i] = l[i] - f[i-k];
    }
    r[n-1] = f[n-1];
    for (int i = n - 2; i >= 0; --i) {
        r[i] = r[i+1] + f[i];
        if (i + k < n) r[i] = r[i] - f[i+k];
    }
    for (int i = 1; i < n; ++i) l[i] = max(l[i], l[i-1]);
    for (int i = n - 2; i >= 0; --i) r[i] = max(r[i], r[i+1]);
    
    int res = f[0];
    for (int i = 1; i < n; ++i) res = max(res, l[i-1] + r[i]);
    
    cout << res << endl;

    return 0;
}
