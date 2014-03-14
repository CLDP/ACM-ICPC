#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);


int N;
double xs, ys, zs, xt, yt, zt;
double x[10], y[10], z[10];
double l[10];

double dist(int a, int b) {
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]) 
              + (z[a] - z[b]) * (z[a] - z[b]));
}


double getL(vector<int> &S, int j) {
    double L = 1e100;
    L = min(L, x[S[j]] - xs);
    L = min(L, xt - x[S[j]]);
    L = min(L, y[S[j]] - ys);
    L = min(L, yt - y[S[j]]);
    L = min(L, z[S[j]] - zs);
    L = min(L, zt - z[S[j]]);
    for (int i = 0; i < j; ++i) L = min(L, dist(S[i], S[j]) - l[i]);
    if (L < 0) return 0;
    return L;
}


int main() {
    int times = 0;
    while (++times) {
        cin >> N;
        if (N == 0) break;
        cin >> xs >> ys >> zs >> xt >> yt >> zt;
        if (xs > xt) swap(xs, xt);
        if (ys > yt) swap(ys, yt);
        if (zs > zt) swap(zs, zt);
        vector<int> S;
        for (int i = 0; i < N; ++i) {
            cin >> x[i] >> y[i] >> z[i];
            S.push_back(i);
        }
        bool flag = false;
        double ans = 0;
        while (S[0] == 0 || flag) {
            for (int i = 0; i < N; ++i) l[i] = getL(S, i);
            double total = 0;
            for (int i = 0; i < N; ++i) total += l[i] * l[i] * l[i];
            if (total > ans) ans = total;
            
            next_permutation(S.begin(), S.end());
            if (S[0] == 0 && flag) break;
            if (S[0] == 1) flag = true;
            if (N == 1) break;
        }
        ans *= 4.0 / 3 * PI;
        ans = (xt - xs) * (yt - ys) * (zt - zs) - ans;
        cout << "Box " << times << ": " << (long long)(ans + 0.5) << endl << endl;
    }
    return 0;
}

