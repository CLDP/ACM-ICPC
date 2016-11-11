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


int main() {
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt) {
        long long a, b, res = 2;
        
        cin >> a >> b;
        if (a < b) {
            long long tmp = a;
            a = b;
            b = tmp;
        }
        
        if ((a != 0) && (b == 0)) res = 3;
        
        while (b > 0) {
            res += a / b;
            long long r = a % b;
            a = b;
            b = r;
        }
        cout << "Case #" << tt << ": " << res-1 << endl;
    }

    return 0;
}
