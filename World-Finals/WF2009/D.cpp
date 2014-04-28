#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-5;
const double PI = acos(-1.0);

struct Point { double x, y;};

double d[4];
Point C[4];

double dis(int a, int b) {
    return sqrt((C[a].x - C[b].x) * (C[a].x - C[b].x) + (C[a].y - C[b].y) * (C[a].y - C[b].y));
}

int cal(Point &X, double a, double b, double R1, double R2, double R, bool flag) {
    double p = R - R1, q = R - R2, r = R1 + R2;
    double theta = atan2(b, a), alpha = acos((p * p + q * q - r * r) / (2 * p * q));
    if (flag) theta -= alpha; else theta += alpha;
    X.x = cos(theta) * (R - R2);
    X.y = sin(theta) * (R - R2);
    return 0;
}

bool check() {
    for (int i = 0; i < 4; ++i)
     for (int j = i + 1; j < 4; ++j) {
         if (dis(i, j) < d[i] + d[j] - EPS) return false;
     }
    return true;
}

int main() {
    int times = 0;
    while (cin >> d[0]) {
        if (d[0] == 0) break;
        cin >> d[1] >> d[2] >> d[3];
        double L = d[0] + d[1], R = d[0] * 5;
        while (L + 1e-5 < R) {
            double mid = (L + R) / 2;
            
            C[0].x = mid - d[0], C[0].y = 0;
            cal(C[3], mid - d[0], 0, d[0], d[3], mid, false);
            cal(C[2], mid - d[0], 0, d[0], d[2], mid, true);
            cal(C[1], C[3].x, C[3].y, d[3], d[1], mid, false);
            
            if (check()) { R = mid; continue; }
            cal(C[1], C[0].x, C[0].y, d[0], d[1], mid, false);
            if (check()) { R = mid; continue; }
            cal(C[1], C[0].x, C[0].y, d[0], d[1], mid, true);
            if (check()) { R = mid; continue; }
            cal(C[1], C[2].x, C[2].y, d[2], d[1], mid, true);
            if (check()) { R = mid; continue; }
            L = mid;
        }
        cout << "Case " << ++times << ": " << round(R) << endl;
    }
    return 0;
}
