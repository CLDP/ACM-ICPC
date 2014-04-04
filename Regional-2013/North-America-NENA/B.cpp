#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;


int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, a, b = 1;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &a);
            if (a == b) ++b;
        }
        printf("%d\n", N - b + 1);
    }
    return 0;
}
