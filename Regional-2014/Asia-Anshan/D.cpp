#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

double x[50010];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        for (int i = 0; i < N; ++i) scanf("%lf", &x[i]);
        sort(x, x + N);
        
        if (N == K) {
            cout << 0 << endl;
            continue;
        }
        
        double sum = 0, sum2 = 0;
        for (int i = 0; i < N - K; ++i) sum += x[i], sum2 += x[i] * x[i];
        
        double ans = sum2 - sum * sum / (N - K);
        
        for (int i = N - K; i < N; ++i) {
            sum += x[i] - x[i - (N - K)];
            sum2 += x[i] * x[i] - x[i - (N - K)] * x[i - (N - K)];
            ans = min(ans, sum2 - sum * sum / (N - K));
        }
        
        printf("%.10lf\n", ans);
    }
    return 0;
}
