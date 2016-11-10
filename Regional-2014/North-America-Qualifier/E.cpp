#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


double x[110], y[110];
double d[110];
bool z[110];

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


int main() {
    double X, Y, A, B;
    cin >> X >> Y >> A >> B;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }
    x[N] = A, y[N] = B;
    ++N;
    
    double ans = dist(X, Y, A, B) / 5;
    
    for (int i = 0; i < N; ++i) {
        d[i] = dist(X, Y, x[i], y[i]) / 5;
        z[i] = false;
    }
    
    for (int i = 0; i < N; ++i) {
        double T = 1e10;
        int v = -1;
        for (int j = 0; j < N; ++j) {
            if (z[j]) continue;
            if (d[j] < T) {
                T = d[j];
                v = j;
            }
        }
        if (v == -1) break;
        z[v] = true;
        for (int i = 0; i < N; ++i) {
            if (z[i]) continue;
            if (dist(x[i], y[i], x[v], y[v]) > 50)
                d[i] = min(d[i], d[v] + 2 + (dist(x[i], y[i], x[v], y[v]) - 50) / 5);
            else
                d[i] = min(d[i], d[v] + 2 + (50 - dist(x[i], y[i], x[v], y[v])) / 5);
        }
    }
    
    ans = min(ans, d[N - 1]);
    printf("%.6lf\n", ans);
    
    return 0;
}
