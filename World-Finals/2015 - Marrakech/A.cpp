#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const int INF = 1000000000;

double p, a, b, c, d;
int n;

double f(int k) {
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main() {
    cin >> p >> a >> b >> c >> d >> n;
    double ans = 0, maxt = -1e100;
    for (int i = 1; i <= n; ++i) {
        maxt = max(maxt, f(i));
        ans = max(maxt - f(i), ans);
    }
    printf("%.8lf\n", ans);
    return 0;
}
