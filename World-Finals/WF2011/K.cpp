#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

double x[110], y[110];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
        x[N] = x[0];
        y[N] = y[0];
        double ans = 1e10;
        
        for (int i = 0; i < N; ++i)
         for (int k = i + 1; k < N; ++k) {
            double A, B, C;
            A = y[k] - y[i];
            B = x[i] - x[k];
            C = x[k] * y[i] - x[i] * y[k];
            double L = 0, R = 0;
            for (int j = 0; j < N; ++j) {
                double D = fabs(A * x[j] + B * y[j] + C) / sqrt(A * A + B * B);
                if (A * x[j] + B * y[j] + C > 0) {
                    L = max(L, D);
                } else {
                    R = max(R, D);
                }
            }
            if (L + R < ans) ans = L + R;
        }
        ans = ans * 100;
        ans = ceil(ans);
        ans = ans / 100;
        printf("Case %d: %.2lf\n", ++times, ans);
    }
    return 0;
}
