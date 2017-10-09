#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 15;

double x[MAXN], y[MAXN], s[MAXN];
double f[1 << MAXN][MAXN];
double poww[MAXN];

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool check(double mid, int N) {
    memset(f, 0, sizeof(f));
    for (int i = 1; i < (1 << N); ++i) {
        int cnt = __builtin_popcount(i);
        if (cnt == 1) {
            int j = 0;
            for (j = 0; j < N; ++j) {
                if (((1 << j) & i) == 0) continue;
                break;
            }
            if ((dist(0, 0, x[j], y[j]) / mid <= s[j])) {
                f[i][j] = dist(0, 0, x[j], y[j]) / mid;
            }
            continue;
        }
        for (int j = 0; j < N; ++j) {
            if (((1 << j) & i) == 0) continue;
            for (int k = 0; k < N; ++k) {
                if (k == j) continue;
                if (((1 << k) & i) == 0) continue;
                if (f[i ^ (1 << j)][k] == 0) continue;
                double TT = f[i ^ (1 << j)][k] + dist(x[j], y[j], x[k], y[k]) / (mid * poww[cnt - 1]);
                if (TT <= s[j]) {
                    if (f[i][j] == 0) f[i][j] = 1e100;
                    f[i][j] = min(f[i][j], TT);
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (f[(1 << N) - 1][i] != 0) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> s[i];
    double K;
    cin >> K;
    poww[0] = 1;
    for (int i = 1; i < N; ++i) poww[i] = poww[i - 1] * K;

    double L = 0, R = 1e7;
    while (L + 1e-5 < R) {
        double mid = (L + R) / 2;
        if (check(mid, N)) R = mid; else L = mid;
    }

    cout << fixed << setprecision(6) << L << endl;

    return 0;
}
