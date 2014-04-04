#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10000010;

int x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN];

double getX(double x1, double y1, double x2, double y2, double Y) {
    return (Y - y1) / (y2 - y1) * (x2 - x1) + x1;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, M, L;
        cin >> N >> M >> L;
        for (int i = 0; i < N; ++i) scanf("%d%d", &x1[i], &y1[i]);
        for (int i = 0; i < M; ++i) scanf("%d%d", &x2[i], &y2[i]);
        int a = 0, b = 0;
        bool flag = (x2[M - 1] - x1[N - 1] >= L);
        if (!flag) {
            cout << "NO" << endl;
            continue;
        }
        for (int i = y1[0]; i < y1[N - 1]; ++i) {
            if (y1[a + 1] <= i) ++a;
            if (y2[b + 1] <= i) ++b;
            double xs = getX(x1[a], y1[a], x1[a + 1], y1[a + 1], i);
            double xt = getX(x2[b], y2[b], x2[b + 1], y2[b + 1], i);
            if (xt - xs + 1e-10 < L) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
