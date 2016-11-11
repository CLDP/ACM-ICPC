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
        long long x, y, x1, x2, y1, y2;
        
        cin >> x >> y >> x1 >> y1 >> x2 >> y2;
        cout << "Case #" << tt << ":" << endl;
        bool sw = false;
        if ((x1 == x2) && (y1 == y2)) {
            cout << x1 << ".0 " << x2 << ".0" << endl;
            continue;
        }
        if (x1 == x2) {
            sw = true;
            long long tmp = x2;
            x2 = y2;
            y2 = tmp;
            tmp = x1;
            x1 = y1;
            y1 = tmp;
        }
        x *= 2;
        y *= 2;
        x1 *= 2;
        y1 *= 2;
        x2 *= 2;
        y2 *= 2;
        long long t = -1;
        long long a1 = abs(x1 - x2) / 2, a2 = (x + x - abs(x2 - x1)) / 2;
        long long b1 = abs(y1 - y2) / 2, b2 = (y + y - abs(y2 - y1)) / 2;
        
        for (long long i = 0; i <= y; ++i) {
            long long cur = i * 2 * x + a1 + x * 2 - max(x1, x2);
            long long rx = x - abs((x1 + cur) % (x * 2) - x);
            long long ry = y - abs((y1 + cur) % (y * 2) - y);
            long long rx2 = x - abs((x2 + cur) % (x * 2) - x);
            long long ry2 = y - abs((y2 + cur) % (y * 2) - y);
            if ((rx == rx2) && (ry == ry2)) {
                if (t == -1)
                    t = cur;
                else
                    t = min(t, cur);
            }
            cur = i * 2 * x + a2 - min(x1, x2);
            rx = x - abs((x1 + cur) % (x * 2) - x);
            ry = y - abs((y1 + cur) % (y * 2) - y);
            rx2 = x - abs((x2 + cur) % (x * 2) - x);
            ry2 = y - abs((y2 + cur) % (y * 2) - y);
            if ((rx == rx2) && (ry == ry2))
                if (t == -1)
                    t = cur;
                else
                    t = min(t, cur);
        }
        
        if (t == -1)
            cout << "Collision will not happen." << endl;
        else {
            long long rx = x - abs((x1 + t) % (x * 2) - x);
            long long ry = y - abs((y1 + t) % (y * 2) - y);
            long long rx2 = x - abs((x2 + t) % (x * 2) - x);
            long long ry2 = y - abs((y2 + t) % (y * 2) - y);
            if (sw) {
                long long tmp = ry;
                ry = rx;
                rx = tmp;
                tmp = ry2;
                ry2 = rx2;
                rx2 = tmp;
            }
            cout << rx / 2 << ".";
            if (rx % 2 == 1)
                cout << "5 ";
            else
                cout << "0 ";
            cout << ry / 2 << ".";
            if (ry % 2 == 1)
                cout << "5" << endl;
            else
                cout << "0" << endl;
        }
    }

    return 0;
}
