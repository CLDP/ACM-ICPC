#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


int main() {
    int N;
    vector<double> x, y;
    
    while (cin >> N) {
        if (N == 0) break;
        x.clear();
        y.clear();
        double l = 0, r = 0;
        for (int i = 0; i < N; ++i) {
            double c, d;
            cin >> c >> d;
            x.push_back(c);
            y.push_back(d);
            if (c < l) l = c;
            if (c > r) r = c;
        }
        
        while (r - l > 1e-7) {
            double lm = 0, rm = 0, mid = (r + l) / 2;
            for (int i = 0; i < N; ++i) {
                if (x[i] <= mid) {
                    lm = max(lm, (x[i] - mid) * (x[i] - mid) + y[i] * y[i]);
                } else {
                    rm = max(rm, (x[i] - mid) * (x[i] - mid) + y[i] * y[i]);
                }
            }
            if (lm > rm) r = mid; else l = mid;
        }
        
        double b = 0;
        for (int i = 0; i < N; ++i) b = max(b, (x[i] - r) * (x[i] - r) + y[i] * y[i]);
        b = sqrt(b);
        
        printf("%.8f %.8f\n", l, b);
    }

    return 0;
}
