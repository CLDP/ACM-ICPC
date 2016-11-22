#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[10], y[10];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
        vector<int> C;
        for (int i = 0; i < N; ++i) C.push_back(i);
        double ans = 0;
        do {
             double L = 0, R = 2000;
             while (L + 1e-5 < R) {
                 double mid = (L + R) / 2;
                 double temp = x[C[0]];
                 bool flag = true;
                 for (int i = 1; i < N; ++i) {
                     temp += mid;
                     if (temp < x[C[i]]) temp = x[C[i]];
                     if (temp > y[C[i]]) flag = false;
                 }
                 if (flag) L = mid; else R = mid;
             }
             if (R > ans) ans = R;
        } while (next_permutation(C.begin(), C.end()));
        int ans1 = ans, ans2 = round((ans - ans1) * 60);
        cout << "Case " << ++times << ": " << ans1 << ":";
        if (ans2 < 10) cout << 0 << ans2 << endl; else cout << ans2 << endl;
    }
    return 0;
}
