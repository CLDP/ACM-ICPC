#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 1010;

double x[MAXN], y[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, T;
    cin >> N >> T;
    double L = 1e10, R = 1e10;
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
        L = min(L, y[i]);
    }
    L = -L;
    while (L + 1e-8 < R) {
        double mid = (L + R) / 2;
        double temp = 0;
        for (int i = 0; i < N; ++i) temp += x[i] / (y[i] + mid);
        if (temp > T) L = mid; else R = mid;
    }
    cout << fixed << setprecision(9) << R << endl;

    return 0;
}
