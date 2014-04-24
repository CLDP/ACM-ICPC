#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const long double EPS = 1e-10;

int N;
pair<int, int> X[100010];

bool check(long double R) {
    long double L = X[0].first + R;
    for (int i = 1; i < N; ++i) {
        if (L < X[i].first) L = X[i].first;
        if (L + R > X[i].second) return false;
        L += R;
    }
    return true;
}


int main() {
    cin >> N;
    long double L = 0, R = 1000000;
    for (int i = 0; i < N; ++i) {
        cin >> X[i].first >> X[i].second;
        R = min(R, (long double)(X[i].second - X[i].first));
    }
    sort(X, X + N);
    while (L + EPS < R) {
        long double mid = (L + R) / 2;
        if (check(mid)) L = mid; else R = mid;
    }
    long long ans1, ans2;
    for (int i = 1; i <= 100000; ++i) {
        long long T = R * i + EPS;
        if (fabs(R * i - T) < EPS * i) {
            ans1 = T;
            ans2 = i;
            break;
        }
    }
    cout << ans1 << "/" << ans2 << endl;
    return 0;
}
