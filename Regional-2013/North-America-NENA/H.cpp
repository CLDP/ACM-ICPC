#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10000010;

char x[MAXN], y[MAXN];
int d[MAXN];


int main() {
    int N;
    cin >> N;
    while (N--) {
        scanf("%s%s", x, y);
        int M = strlen(x);
        for (int i = 0; i < M; ++i) d[i] = x[i] - y[i];
        
        int ans = 0, diff = 0;
        for (int i = 0; i < M; ++i) {
            if (diff == 0) {
                ans += abs(d[i]);
            } else 
            if (diff > 0) {
                if (d[i] <= 0) {
                    ans += abs(d[i]);
                } else {
                    if (d[i] > diff) ans += d[i] - diff;
                }
            } else {
                if (d[i] >= 0) {
                    ans += abs(d[i]);
                } else {
                    if (d[i] < diff) ans += abs(d[i] - diff);
                }
            }
            diff = d[i];
        }
        cout << ans << endl;
    }
    return 0;
}
