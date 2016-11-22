#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

struct hill {
    double x, h, b;
};

int N;
hill X[110];

int getL(double &A, double &B, double &C, double x1, double y1, double x2, double y2) {
    A = y2 - y1;
    B = x1 - x2;
    C = x2 * y1 - x1 * y2;
    return 0;
}

double cal(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    if ((y2 - y1) * (x4 - x3) == (y4 - y3) * (x2 - x1)) return 1e100;
    double A1, B1, C1, A2, B2, C2;
    getL(A1, B1, C1, x1, y1, x2, y2);
    getL(A2, B2, C2, x3, y3, x4, y4);
    return (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
}

double getH(double xx) {
    double H = 0;
    for (int i = 0; i < N; ++i) {
        double x1 = X[i].x - X[i].b / 2, x2 = X[i].x + X[i].b / 2;
        if (x1 <= xx && xx <= X[i].x) H = max(H, (xx - x1) / (X[i].x - x1) * X[i].h);
        if (X[i].x <= xx && xx <= x2) H = max(H, (x2 - xx) / (x2 - X[i].x) * X[i].h);
    }
    return H;
}

int main() {
    int times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].h >> X[i].b;
        vector<double> T;
        for (int i = 0; i < N; ++i) {
            T.push_back(X[i].x);
            T.push_back(X[i].x - X[i].b / 2);
            T.push_back(X[i].x + X[i].b / 2);
            double xi1 = X[i].x - X[i].b / 2, xi2 = X[i].x + X[i].b / 2;
            for (int j = i + 1; j < N; ++j) {
                double xx;
                double xj1 = X[j].x - X[j].b / 2, xj2 = X[j].x + X[j].b / 2;
                xx = cal(xi1, 0, X[i].x, X[i].h, xj1, 0, X[j].x, X[j].h);
                if (xi1 <= xx && xx <= X[i].x && xj1 <= xx && xx <= X[j].x) T.push_back(xx);
                xx = cal(xi2, 0, X[i].x, X[i].h, xj1, 0, X[j].x, X[j].h);
                if (X[i].x <= xx && xx <= xi2 && xj1 <= xx && xx <= X[j].x) T.push_back(xx);
                xx = cal(xi1, 0, X[i].x, X[i].h, xj2, 0, X[j].x, X[j].h);
                if (xi1 <= xx && xx <= X[i].x && X[j].x <= xx && xx <= xj2) T.push_back(xx);
                xx = cal(xi2, 0, X[i].x, X[i].h, xj2, 0, X[j].x, X[j].h);
                if (X[i].x <= xx && xx <= xi2 && X[j].x <= xx && xx <= xj2) T.push_back(xx);
            }
        }
        sort(T.begin(), T.end());
        double ans = 0;
        for (int i = 1; i < T.size(); ++i) {
            double a = getH(T[i - 1]), b = getH(T[i]);
            if (fabs(a + b) < 1e-5) continue;
            ans += sqrt((a - b) * (a - b) + (T[i - 1] - T[i]) * (T[i - 1] - T[i]));
        }
        printf("Case %d: %.0lf\n\n", ++times, ans);
    }
    return 0;
}
