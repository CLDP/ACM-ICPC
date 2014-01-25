#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int x[1000001];

bool check(int a) {
    int left = 0, get = 0;
    for (int i = 0; i < 2 * N * K; ) {
        if (x[i+1] - x[i] <= a) {
            ++get;
            left += 2 * K - 2;
            i += 2;
            if (get == N) return true;
        } else {
            if (left == 0) return false;
            --left;
            ++i;
        }
    }
    return true;
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < 2 * N * K; ++i) cin >> x[i];
    sort(x, x + 2 * N * K);
    if (check(0)) {
        cout << 0 << endl;
        return 0;
    }
    int L = 0, R = x[2 * N * K - 1] - x[0];
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        if (check(mid))
            R = mid;
        else
            L = mid;
    }
    cout << R << endl;
    
    return 0;
}
