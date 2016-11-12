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

int a[20005];
int n, k;

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int ll = 0, rr = 1000001;
    while (ll + 1 < rr) {
        int mm = (ll + rr) / 2;
        int cnt = 0, cur = 1, ind = 0;
        bool fail = false;
        while (ind < n) {
            cur = gcd(cur, a[ind]);
            if (cur == 1) {
                ++cnt;
                if (cnt > k) {
                    fail = true;
                    break;
                }
                cur = a[ind];
                int acc = 1;
                for (int i = 2; i * i <= cur; ++i) {
                    while (cur % i == 0) {
                        cur = cur / i;
                        if (i >= mm) acc *= i;
                    }
                }
                if (cur >= mm) acc *= cur;
                if (acc == 1) {
                    fail = true;
                    break;
                }
                cur = acc;
            }
            ++ind;
        }
        if (!fail && ind == n)
            ll = mm;
        else
            rr = mm;
    }
    
    cout << ll << endl;
    
    return 0;
}
