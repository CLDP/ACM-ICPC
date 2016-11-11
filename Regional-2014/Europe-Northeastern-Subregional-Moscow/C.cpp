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


int main() {
    long long A, B, C;
    cin >> A >> B >> C;
    if (A >= B) {
        cout << (C + B - 1) / B << " " << (C + B - 1) / B << endl;
        return 0;
    }
    long long ans1 = (C + A - 1) / A;
    long long L = 0, R = ans1;
    while (L + 1 < R) {
        long long mid = (L + R) >> 1;
        long long P = ans1 / mid;
        long long Q = ans1 % mid;
        if (Q * min(B, (P + 1) * A) + (mid - Q) * min(B, P * A) >= C) R = mid; else L = mid;
    }
    cout << ans1 << " " << R << endl;
    return 0;
}
