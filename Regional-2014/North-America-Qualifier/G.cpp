#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

double x[200], y[200];

double dist2(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double dist(int a, int b) {
    return dist2(x[a], y[a], x[b], y[b]);
}


int getmid(int a, int b, double R, double &xx, double &yy, bool small) {
    double xm = (x[a] + x[b]) / 2, ym = (y[a] + y[b]) / 2;
    if (y[a] != y[b]) {
        double K = (x[a] - x[b]) / (y[b] - y[a]);
        double B = ym - K * xm;
        double xL = xm, xR = 1000;
        while (xL + 1e-8 < xR) {
            double xM = (xL + xR) / 2;
            if (dist2(xM, K * xM + B, x[a], y[a]) - 1e-6 < R) xL = xM; else xR = xM;
        }
        if (!small) xx = xm - (xL - xm);
        xx = xL, yy = K * xL + B;
        return 0;
    }
    
    double xL = xm, xR = 1000;
    while (xL + 1e-8 < xR) {
        double xM = (xL + xR) / 2;
        if (dist2(xM, ym, x[a], y[a]) - 1e-6 < R) xL = xM; else xR = xM;
    }
    if (!small) xx = xm - (xL - xm);
    xx = xL, yy = ym;
    return 0;
}


int ans;

int newans(double xx, double yy, double R, double N) {
    int temp = 0;
    for (int i = 0; i < N; ++i)
     if (dist2(xx, yy, x[i], y[i]) - 1e-5 < R) ++temp;
    if (temp > ans) ans = temp;
    return 0;
}


int main() {
    int times;
    cin >> times;
    int N;
    double R;
    while (times--) {
        cin >> N >> R;
        R /= 2;
        ans = 1;
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
        if (N == 1) {
            cout << 1 << endl;
            continue;
        }
        for (int i = 0; i < N; ++i)
         for (int j = i + 1; j < N; ++j) {
             if (dist(i, j) >= R * 2 + 1e-5) continue;
             double a, b;
             getmid(i, j, R, a, b, false);
             newans(a, b, R, N);
             getmid(i, j, R, a, b, true);
             newans(a, b, R, N);
         }
        cout << ans << endl;
    }

    return 0;
}
