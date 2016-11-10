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

int n, m;

int main() {
    freopen("alter.in", "r", stdin);
    freopen("alter.out", "w", stdout);
    cin >> n >> m;
    
    cout << (n / 2 + m / 2) << endl;
    
    for (int i = 2; i <= n; i += 2)
        cout << i << " 1 " << i << " " << m << endl;
    for (int j = 2; j <= m; j += 2)
        cout << "1 " << j << " " << n << " " << j << endl;

    return 0;
}
