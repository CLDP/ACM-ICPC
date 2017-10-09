#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 1010;

long double f(long double a, long double d, long double s) {
    return a + s - a / 2 * (exp(d / (2 * a)) + exp(-d / (2 * a)));
}

long double fl(long double a, long double d, long double s) {
    return a * (exp(d / (2 * a)) - exp(-d / (2 * a)));
}

int main() {
    ios_base::sync_with_stdio(false);
    long double d, s;
    cin >> d >> s;

    long double L = 0, R = 1e200;
    while (L + 1e-12 < R) {
        long double mid = (L + R) / 2;
        if (f(mid, d, s) < 0) L = mid; else R = mid;
    }

    cout << fixed << setprecision(8) << fl(L, d, s) << endl;

    return 0;
}
