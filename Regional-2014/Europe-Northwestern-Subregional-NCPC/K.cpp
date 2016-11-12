#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    long long c, n, t = 0;
    
    cin >> c >> n;
    
    for (int i = 0; i < n; ++i) {
        long long x, y, z;
        cin >> x >> y >> z;
        if (x > t) {
            cout << "impossible" << endl;
            return 0;
        }
        t = t - x;
        t = t + y;
        if (t > c) {
            cout << "impossible" << endl;
            return 0;
        }
        if ((z > 0) && (t < c)) {
            cout << "impossible" << endl;
            return 0;
        }
    }
    
    if (t != 0) {
       cout << "impossible" << endl;
       return 0;
    }

    cout << "possible" << endl;        

    return 0;
}
