#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10010;

int x[MAXN], y[MAXN];

int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;
        int a, b, c, d;
        for (int i = 0; i < N; ++i) {
            cin >> a >> b >> c >> d;
            x[i] = c;
            y[i] = c + d - 1;
        }
        for (int i = 0; i < M; ++i) {
            cin >> a >> b;
            b = a + b - 1;
            int ans = 0;
            for (int j = 0; j < N; ++j) {
                if ((x[j] <= a && a <= y[j]) || (x[j] <= b && b <= y[j]) 
                 || (a <= x[j] && x[j] <= b) || (a <= y[j] && y[j] <= b)) ++ans;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
