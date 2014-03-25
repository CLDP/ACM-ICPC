#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1002;
const double INF = 1e20;

double x[MAXN], y[MAXN], c[MAXN], d[MAXN], dd[MAXN];
int f[MAXN];
bool z[MAXN];


int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        double total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> x[i] >> y[i] >> c[i];
            d[i] = INF;
            z[i] = false;
            total += c[i];
        }
        d[0] = dd[0] = 0;
        
        double ans = 0;
        for (int i = 0; i < N; ++i) {
            int a = -1;
            double b = INF;
            for (int j = 0; j < N; ++j) {
                if (z[j] || d[j] > b) continue;
                a = j;
                b = d[j];
            }
            
            dd[a] = max(d[a], dd[f[a]]);
            ans += dd[a] * c[a];
            z[a] = true;
            
            for (int j = 0; j < N; ++j) {
                if (z[j]) continue;
                double D = sqrt((x[a] - x[j]) * (x[a] - x[j]) + (y[a] - y[j]) * (y[a] - y[j]));
                if (D < d[j]) {
                    d[j] = D;
                    f[j] = a;
                }
            }
        }

        cout << "Island Group: " << ++times << " Average ";
        printf("%.2lf\n\n", ans / total);
    }
    return 0;
}
