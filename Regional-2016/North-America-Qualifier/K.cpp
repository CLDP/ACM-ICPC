#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        int l1, a1, l2, a2, lt, at;
        cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;
        int ans = 0;
        int A, B;
        for (int i = 1; i * l1 <= lt; ++i) {
            if (i * a1 > at) break;
            if ((lt - i * l1) % l2 != 0) continue;
            if ((at - i * a1) % a2 != 0) continue;
            int a = (lt - i * l1) / l2;
            int b = (at - i * a1) / a2;
            if (a != b) continue;
            if (a == 0) continue;
            ++ans;
            A = i;
            B = b;
        }
        if (ans != 1) {
            cout << "?" << endl;
            continue;
        }
        cout << A << " " << B << endl;
    }
    return 0;
}
