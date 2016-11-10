#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int N, A, B;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A >> B;
        if (A > B) swap(A, B);
        long long ans = 1;
        long long temp = 2;
        while (true) {
            --temp;
            if (temp > A + B) break;
            if (temp <= A) {
                ans += temp + 1;
            } else 
            if (temp <= B) {
                ans += A + 1;
            } else {
                ans += A + B - temp + 1;
            }
            temp = (temp + 1) * 2;
        }
        cout << ans << endl;
    }

    return 0;
}
