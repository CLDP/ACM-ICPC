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

int x[101000];


int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) scanf("%d", &x[i]);
    sort(x, x + N);
    int ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (x[i] <= x[N - 1]) {
            ++ans;
            x[N - 1] -= x[i];
        }
    } 
    cout << ans + 1 << endl;
    return 0;
}
