#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

double calH(double air, double space, double l, double r, double h) {
    double mid = (r + l) / 2;
    while (r - l > 1e-6) {
        if (mid * 0.097 + air / (space - mid) > 0.097 * h + 1)
            r = mid;
        else
            l = mid;
        mid = (r + l) / 2;
    }
    return l;
}

int main() {
    int N, times = 0;
    double h[11], p[11];
    double v, l, r, res = 0, mid;
    
    while (cin >> N) {
        if (N == 0) break;
        
        for (int i = 0; i < N; ++i) cin >> h[i];
        for (int i = 0; i < N - 1; ++i) cin >> p[i];
        double air = h[1] - p[0];
        for (int i = 2; i < N; ++i) air += h[i];
        double space = air;
        
        res = h[0];
        bool arr = true;
        for (int i = 1; i < N - 1; ++i) {
            if (p[i] * 0.097 + air / (space + p[i - 1] - p[i]) > 0.097 * h[0] + 1) {
                res += calH(air, space + p[i - 1], p[i - 1], p[i], h[0]);
                arr = false;
                break;
            } else {
                space = space + p[i - 1];
                if (air / (space - p[i] - p[i]) > 0.097 * (h[0] - p[i]) + 1) {
                    res += space - air / (0.097 * (h[0] - p[i]) + 1);
                    arr = false;
                    break;
                } else {
                    double airT = air * (h[i] - p[i]) / (space - p[i] - p[i]);
                    res += calH(airT, h[i], p[i], h[i], h[0]);
                    air = air - airT;
                    space = space - p[i] - h[i];
                }
            }   
        }
        
        if (arr) res += calH(air, space + p[N - 2], p[N - 2], h[N - 1], h[0]);
        printf("Case %d: %.3f\n\n", ++times, res);
    }
    
    return 0;
}
