#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
 
string S;
int result;
 
int solve(int x, int L, int N, int ones) {
    if (result > 1) return 0;
    if (L < N || N < 0) return 0;
    if (x == S.size()) {
        result += L == 0;
        return 0;
    }
    if (S[x] == '1') {
        if (ones <= 1) solve(x + 1, L - 1, N - 1, ones + 1);
        int sz = 0;
        for (int i = x; ones == 0 && i < S.size() && sz <= N; ++i) {
            sz = 2 * sz + (S[i] == '1' ? 1 : 0);
            if (sz >= 3) solve(i + 1, L - sz, N - sz, sz); 
        }
    } else {
        solve(x + 1, L - 1, N, 0);
    }
    return 0;
}
 
int main() {
    int times = 0, L, N;
    while (cin >> L >> N) {
        if (L == 0) break;
        cin >> S;
        result = 0;
        solve(0, L, N, 0);
        cout << "Case #" << ++times << ": ";
        if (result == 0) {
            cout << "NO" << endl;
        } else if (result == 1) {
            cout << "YES" << endl;
        } else {
            cout << "NOT UNIQUE" << endl;
        }
    }
    return 0;
}
