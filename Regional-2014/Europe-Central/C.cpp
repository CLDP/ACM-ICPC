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
        int N;
        cin >> N;
        bool flag = false;
        for (int i = 2; i * (i + 1) / 2 <= N; ++i) {
            if (i & 1) {
                if (N % i != 0) continue;
                flag = true;
                printf("%d = %d", N, N / i - (i - 1) / 2);
                for (int j = N / i - (i - 1) / 2 + 1; j <= N / i + (i - 1) / 2; ++j) printf(" + %d", j);
                printf("\n");
                break;
            } else {
                if (N % (i / 2) != 0) continue;
                if (N / (i / 2) % 2 == 0) continue;
                int a = N / (i / 2) / 2;
                printf("%d = %d", N, a - i / 2 + 1);
                for (int j = a - i / 2 + 2; j <= a + i / 2; ++j) printf(" + %d", j);
                printf("\n");
                flag = true;
                break;
            }
        }
        if (!flag) cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
