#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

double T[1010], X[1010], Y[1010];

int main() {
    int TT;
    cin >> TT;
    while (TT--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) cin >> T[i] >> X[i] >> Y[i];
        
        double ans = 0;
        for (int i = 1; i < N; ++i) {
            ans = max(ans, sqrt((Y[i] - Y[i-1]) * (Y[i] - Y[i - 1]) + (X[i] - X[i - 1]) * (X[i] - X[i - 1])) / (T[i] - T[i - 1]));
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}
