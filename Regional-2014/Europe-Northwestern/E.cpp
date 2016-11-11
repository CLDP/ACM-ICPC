#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long double N, P, S, V;

long double getP(long double A) {
    return N / P / 1e9 * log(log(N) / log(2)) * sqrt(2) * pow(log(N) / log(2), A * sqrt(2))
         - S / V / A / A;
}

int main() {
    cin >> N >> P >> S >> V;
    long double L = 0, R = 1e100;
    while (L + 1e-8 < R) {
        long double mid = (L + R) / 2;
        if (getP(mid) > 0) R = mid; else L = mid;
        
    }
    long double ans = N / P / 1e9 * pow(log(N) / log(2), R * sqrt(2)) + S / V * (1 + 1 / R);
    printf("%.8lf %.8lf\n", (double)ans, (double)R);
    return 0;
}
