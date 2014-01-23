#include <iostream>
#include <cstdio>
using namespace std;


int main() {
    double x, p;
    cin >> x >> p;
    x /= 100;
    p /= 100;
    if (p == 0) {
        cout << 0 << endl;
        return 0;
    }
    double r = (1 - p) / p;
    double ans = 0, rw = 1, rl = 1;
    for (int W = 0; W < 2500; ++W) {
        rl = 1;
        for (int L = 0; L > -21000; --L) {
            if (rw == rl) {
                rl /= r;
                continue;
            }
            double prob = (1 - rl) / (rw - rl);
            double expect = prob * W + (1 - prob) * L * (1 - x);
            if (expect > ans) ans = expect;
            
            rl /= r;
            if (rl < 1e-20) rl = 0;
        }
        rw *= r;
    }
    
    printf("%.9lf\n", ans);
    
    return 0;
}
