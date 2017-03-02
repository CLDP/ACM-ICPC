#include <iostream>
#include <algorithm>
using namespace std;

const double INF = 2 * 1e18;

int main() {
    long long A, B;
    cin >> A >> B;
    long long ans = 10;

    for (long long T = 11; T < 100000; ++T) {
        long long C = 0, temp = B, K = 1;
        while (temp > 0) {
            C += temp % 10 * K;
            K *= T;
            temp /= 10;
        }
        if (C > A) break;

        bool flag = true;
        temp = A;
        C = 0;
        K = 1;
        while (temp > 0) {
            if (temp % T > 9) {
                flag = false;
                break;
            }
            C += temp % T * K;
            K *= 10;
            temp /= T;
        }
        if (flag) ans = T;
    }
    for (long long T = B; T < 100000; ++T) {
        long long L = 10, R = 1LL * 1000000000 * 1000000000 + 2;
        while (L + 1 < R) {
            long long mid = (L + R) / 2;
            double mm = 1;
            double temp = 0;
            long long TT = T;
            while (TT > 0) {
                temp += TT % 10 * mm;
                mm *= mid;
                TT /= 10;
            }
            if (temp > INF) {
                R = mid;
                continue;
            }

            long long cnt = 0;
            TT = T;
            long long mmm = 1;
            while (TT > 0) {
                cnt += TT % 10 * mmm;
                mmm *= mid;
                TT /= 10;
            }
            if (cnt > A) R = mid;
            if (cnt < A) L = mid;
            if (cnt == A) {
                ans = max(ans, mid);
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
