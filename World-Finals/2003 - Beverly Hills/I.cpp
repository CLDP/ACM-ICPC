#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-6;

double getX(const double &A, const double &B, double Y) {
    return sqrt(1 - Y * Y / (B * B)) * A;
}

double getY(const double &A, const double &B, double X) {
    return sqrt(1 - X * X / (A * A)) * B;
}

double getT(double a2, double b2, double S, int D) {
    double L = 0, R = PI / 2;
    while (L + EPS < R) {
        double mid = (L + R) / 2;
        double SS = - a2 * b2 / 2 * (sin(2 * mid) / 2 - mid);
        double c2 = sqrt(a2 * a2 - b2 * b2);
        switch (D) {
            case 1 : SS += (a2 * cos(mid) - c2) * (b2 * sin(mid)) / 2; break;
            case 2 : SS += (a2 * cos(mid) + c2) * (b2 * sin(mid)) / 2; break;
            case 3 : SS += (a2 * cos(mid) + c2) * (b2 * sin(mid)) / 2; break;
            case 4 : SS += (a2 * cos(mid) - c2) * (b2 * sin(mid)) / 2; break;
        }
            
        if (SS > S) R = mid; else L = mid;
    }
    return R;
}

int main() {
    int times = 0;
    double a1, b1, t1, a2, b2, t;
    while (cin >> a1 >> b1 >> t1 >> a2 >> b2 >> t) {
        if (a1 == 0) break;
        cout << "Solar System " << ++times << ": ";
        double t2 = t1 * sqrt((a2 * a2 * a2) / (a1 * a1 * a1));
        double S = PI * a2 * b2 / 2;
        double c2 = sqrt(a2 * a2 - b2 * b2);
        t -= floor(t / t2) * t2;
        
        double x, y;
        if (t < t2 / 2) {
            if (t < t2 / 4) {
                double T = getT(a2, b2, S * t / (t2 / 2), 1);
                x = a2 * cos(T), y = b2 * sin(T);
            } else {
                double T = getT(a2, b2, S * (1 - t / (t2 / 2)), 2);
                x = a2 * cos(PI - T), y = b2 * sin(PI - T);
            }
        } else {
            t -= t2 / 2;
            if (t < t2 / 4) {
                double T = getT(a2, b2, S * t / (t2 / 2), 3);
                x = a2 * cos(PI + T), y = b2 * sin(PI + T);
            } else {
                double T = getT(a2, b2, S * (1 - t / (t2 / 2)), 4);
                x = a2 * cos(2 * PI - T), y = b2 * sin(2 * PI - T);
            }
        }
        printf("%.3lf %.3lf\n", x, y);
    }
    return 0;
}
