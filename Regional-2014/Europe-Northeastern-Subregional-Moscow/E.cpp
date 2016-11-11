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
    long long N, D;
    cin >> N >> D;
    if (N < D) {
        cout << "2 0" << endl;
        return 0;
    }
    if ((N == 0) && (D == 0)) {
        cout << "2 1" << endl;
        return 0;
    }
    if (N == D) {
        cout << N + 1 << " " << 1 << endl;
        return 0;
    }
    N -= D;
    long long ans1 = 0, ans2 = 0;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i == 0 && i > D && (i > 1)) {
            long long temp = N / i, temp2 = 1;
            while (temp % i == D) {
                temp /= i;
                ++temp2;
            }
            if (temp2 > ans2) {
                ans2 = temp2;
                ans1 = i;
            } else
            if (temp2 == ans2) {
                ans1 = min(ans1, i);
            }
        }
        
        long long j = N / i;
        if (N % j == 0 && j > D && (j > 1)) {
            long long temp = N / j, temp2 = 1;
            while (temp % j == D) {
                temp /= j;
                ++temp2;
            }
            if (temp2 > ans2) {
                ans2 = temp2;
                ans1 = j;
            } else
            if (temp2 == ans2) {
                ans1 = min(ans1, j);
            }
        }
    }
    
    if (ans1 == 0) {
        cout << "2 0" << endl;
        return 0;
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
