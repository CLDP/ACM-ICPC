#include <vector>
#include <set>
#include <stack>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[220000];

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    int T = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &x[i]);
        T = min(x[i], T);
    }
    stack<int> P;
    
    long long temp = 0, ans = 0;
    for (int i = 0; i < K; ++i) {
        temp += x[i];
        if (x[i] > T) P.push(i);
    }
    for (int i = K - 1; i < N; ++i) {
        if (x[i] > T) P.push(i);
        while (temp >= 0) {
            int a = P.top();
            P.pop();
            
            long long A = min(temp + 1, (long long)x[a] - T);
            x[a] -= A;
            ans += A;
            temp -= A;
            
            if (x[a] > T) P.push(a);
        }
        temp += x[i + 1] - x[i + 1 - K];
    }
    cout << ans << endl;
    for (int i = 0; i < N; ++i) printf("%d ", x[i]);
    printf("\n");
    return 0;
}
