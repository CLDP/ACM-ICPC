#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);

double cal(double r, double R, double D) {
    if (D >= R + r - 1e-8) return 0;
    if (D <= R - r + 1e-8) return PI * r * r;
    double X = (R * R - r * r) / D;
    if (X > D) {
        double d1 = (X - D) / 2;
        double d2 = (X + D) / 2;
        double ang1 = 2 * acos(d1 / r);
        double ang2 = 2 * acos(d2 / R);
        return (PI * r * r * (2 * PI - ang1) / (2 * PI) + 0.5 * r * r * sin(ang1))
             + (PI * R * R * ang2 / (2 * PI) - 0.5 * R * R * sin(ang2));
    } else {
        double d1 = (D - X) / 2;
        double d2 = (D + X) / 2;
        double ang1 = 2 * acos(d1 / r);
        double ang2 = 2 * acos(d2 / R);
        return (PI * r * r * ang1 / (2 * PI) - 0.5 * r * r * sin(ang1)) 
             + (PI * R * R * ang2 / (2 * PI) - 0.5 * R * R * sin(ang2));
    }
    return 0;
}

int main() {
    int times;
    cin >> times;
    for (int tt = 1; tt <= times; ++tt) {
        double r, R;
        scanf("%lf%lf", &r, &R);
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        double D = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        
        printf("Case #%d: ", tt);
        printf("%.6lf\n", cal(R, R, D) - cal(r, R, D) * 2 + cal(r, r, D));
        
    }
    return 0;
}
