#include <iostream>
using namespace std;

const int MAXN = 20000;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int x[MAXN], y[MAXN];
    int times = 0;
    while (a != 0 || b != 0 || c!= 0 || d != 0) {
        int e, f;
        ++times;
        e = 0, f = 0;
        x[0] = a - c;
        for (int n = 1; n < MAXN; ++n) x[n] = x[n-1] + a;
        y[0] = b - d;
        for (int m = 1; m < MAXN; ++m) y[m] = y[m-1] + b;
        
        int l = 0, r = 0;
        bool flag = false;
        while (l < MAXN && r < MAXN) {
            if (x[l] < y[r]) {
                ++l;
                continue;
            }
            if (x[l] > y[r]) {
                ++r;
                continue;
            } 
            flag = true;
            break;
        }
        
        if (flag) {
            cout << "Case " << times << ": " << x[l] / a << " " << x[l] % a << "/" << a << endl;
        } else {
            cout << "Case " << times << ": Never" << endl;
        }
        cin >> a >> b >> c >> d;
    }
    return 0;
}
