#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const double EPS = 1e-8;

double f[1010];

int main() {
    int N;
    double W, H;
    cin >> W >> H >> N;
    double R = 1.0 * (W + H) / (W - H);
    double h = 1.0 * H / W;
    f[0] = pow((h + 1) / 2, 2) * 2;
    vector<double> XX;
    for (int i = 1; i <= N; ++i) {
        double A = pow(1.0 / (R + 1), 2) + pow(h - R / (R + 1), 2) - h * h + f[i - 1];
        double B = -2.0 * (h + 1 / (R + 1)) / (R + 1) + 2.0 * R / (R + 1) * (h - R / (R + 1));
        double X = -B / (2 * A);
        XX.push_back(X);
        f[i] = X * X * f[i - 1] + pow((1 / (R + 1) + h) - X / (R + 1), 2) + pow(R / (R + 1) + X * (h - R / (R + 1)), 2) - pow(X * h, 2);
    }
    printf("%.6lf\n", f[N] * W * W / 2);
    vector<double> ans;
    for (int i = N - 1; i >= 0; --i) {
        ans.push_back(W * XX[i]);
        W *= XX[i];
    }
    for (int i = N - 1; i >= max(0, N - 10); --i) {
        printf("%.6lf\n", ans[i]);
    }

    return 0;
}
