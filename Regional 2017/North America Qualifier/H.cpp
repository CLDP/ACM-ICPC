#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 1010;

int x[MAXN], y[MAXN], t[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, T;
    cin >> N >> T;
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> t[i];
    double ans = 0;
    for (int i = 1; i < N; ++i) {
        ans += sqrt(1.0 * (x[i] - x[i - 1]) * (x[i] - x[i - 1]) + 1.0 * (y[i] - y[i - 1]) * (y[i] - y[i - 1]));
    }
    t[N] = 100000000;

    vector<double> X, Y;
    X.push_back(x[0]);
    Y.push_back(y[0]);
    int p = 0;
    for (int tt = T; tt < t[N - 1]; tt += T) {
        while (tt > t[p]) ++p;
        double xx = x[p - 1] + 1.0 * (x[p] - x[p - 1]) * (tt - t[p - 1]) / (t[p] - t[p - 1]);
        double yy = y[p - 1] + 1.0 * (y[p] - y[p - 1]) * (tt - t[p - 1]) / (t[p] - t[p - 1]);
        X.push_back(xx);
        Y.push_back(yy);
    }
    X.push_back(x[N - 1]);
    Y.push_back(y[N - 1]);
    double ans2 = 0;
    for (int i = 1; i < X.size(); ++i) {
        ans2 += sqrt(1.0 * (X[i] - X[i - 1]) * (X[i] - X[i - 1]) + 1.0 * (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));
    }


    cout << fixed << setprecision(8) << (ans - ans2) / ans * 100 << endl;

    return 0;
}
