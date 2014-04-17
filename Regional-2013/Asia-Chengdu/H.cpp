#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const char S[9] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};

int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int A;
        string P;
        cin >> A >> P;
        double C = 1, D = 1;
        for (int j = 0; j < 9; ++j) {
            if (S[j] == P[1]) break;
            C = C * 1024;
            D = D * 1000;
        }
        double ans = (1 - D / C) * 100;
        printf("Case #%d: %.2lf\%\n", i, ans);
    }
    return 0;
}
