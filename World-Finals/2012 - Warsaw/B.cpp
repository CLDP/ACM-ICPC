#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;

const double PI = acos(-1.0);

int n;
long double y[100], x[100];

long double f(long double a) {
    long double ans = 0, xx = a;
    for (int i = 0; i <= 2 * n; ++i) {
        ans += x[i] * xx;
        xx *= a;
    }
    return ans;
}

int main() {
    int times = 0;
    while (cin >> n) {
        ++times;
        for (int i = 0; i < n + 1; ++i) cin >> y[i];
        
        for (int i = 0; i <= 2 * n; ++i) {
            x[i] = 0;
            for (int j = 0; j <= i; ++j) x[i] += y[j] * y[i-j];
            x[i] = x[i] / (i + 1) * PI;
        }
        
        double a, b, c;
        cin >> a >> b >> c;
        double base = f(a), top = f(b);
        printf("Case %d: %.2lf\n", times, top - base);
        if (top - base < c) {
            cout << "insufficient volume" << endl;
        } else {
            double basec = c;
            int tt = 0;
            while (c <= top - base) {
                double l = a, r = b;
                while (l < r - 1e-10) {
                    double mid = (l + r) / 2;
                    double man = f(mid) - base;
                    if (man > c) 
                        r = mid;
                    else
                        l = mid;
                }
                printf("%.2lf", l - a);
                ++tt;
                c += basec;
                if (tt == 8) break; 
                if (c <= top - base) cout << " ";
            }
            cout << endl;
        }
        
    }
    
    return 0;
}
