#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int A[MAXN], B[MAXN];

int cal(int A, int B, int T) {
    int D = abs(A - B);
    T %= (D * 2);
    if (T > D) {
        T -= D;
        if (A < B) {
            return B - T;
        } else {
            return B + T;
        }
    } else {
        if (A < B) {
            return A + T;
        } else {
            return A - T;
        }
    }
    return 0;
}


int main() {
    freopen("knockout.in", "r", stdin);
    freopen("knockout.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];
    for (int i = 0; i < M; ++i) {
        int a, b, t, ans = 0;
        cin >> a >> b >> t;
        for (int j = 0; j < N; ++j) {
            int P = cal(A[j], B[j], t);
            if (a <= P && P <= b) ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}
