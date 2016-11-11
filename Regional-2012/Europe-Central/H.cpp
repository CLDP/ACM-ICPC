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
    int T;
    cin >> T;
    while (T--) {
        int N, a, b;
        cin >> N;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &a, &b);
            for (int j = 1; j <= 10; ++j) {
                int k = j * 20;
                if (a * a + b * b <= k * k) {
                    ans += 11 - j;
                    break;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
