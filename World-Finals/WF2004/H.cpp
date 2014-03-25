#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

struct seg {
    double x1, y1, x2, y2;
};

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int getP(double &xx, double &yy, seg X, seg Y) {
    double delta = (X.x2 - X.x1) * (Y.y1 - Y.y2) - (Y.x2 - Y.x1) * (X.y1 - X.y2);
    xx = ((Y.y1 * Y.x2 - Y.x1 * Y.y2) * (X.x2 - X.x1) - 
          (X.y1 * X.x2 - X.x1 * X.y2) * (Y.x2 - Y.x1)) / delta;
    yy = ((X.y1 * X.x2 - X.x1 * X.y2) * (Y.y1 - Y.y2) - 
          (Y.y1 * Y.x2 - Y.x1 * Y.y2) * (X.y1 - X.y2)) / delta;
    return 0;
}


int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        vector<seg> X(N);
        for (int i = 0; i < N; ++i) cin >> X[i].x1 >> X[i].y1 >> X[i].x2 >> X[i].y2;
        
        int total = 0;
        for (int i = 0; i < N; ++i) {
            double DD = dist(X[i].x1, X[i].y1, X[i].x2, X[i].y2);
            vector<double> P;
            
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (fabs((X[i].y2 - X[i].y1) * (X[j].x2 - X[j].x1) - 
                    (X[j].y2 - X[j].y1) * (X[i].x2 - X[i].x1)) < 1e-5) continue;
                
                double xx, yy;
                getP(xx, yy, X[i], X[j]);
                double D1 = dist(xx, yy, X[i].x1, X[i].y1);
                double D2 = dist(xx, yy, X[i].x2, X[i].y2);
                if (fabs(DD - D1 - D2) > 1e-5) continue;
                if (fabs(dist(X[j].x1, X[j].y1, X[j].x2, X[j].y2) - 
                    dist(xx, yy, X[j].x1, X[j].y1) - dist(xx, yy, X[j].x2, X[j].y2)) > 1e-5) continue;
                P.push_back(D1);
            }
            
            int ans = 0;
            if (P.size() > 0) {
                sort(P.begin(), P.end());
                if (P[0] + EPS > 25)
                    ans = (P[0] - 25 + EPS) / 50 + 1;
                for (int i = 1; i < P.size(); ++i) {
                    if (P[i] - P[i-1] - 50 + EPS > 0)
                        ans += (P[i] - P[i-1] - 50 + EPS) / 50 + 1;
                }
                if (DD - P[P.size() - 1] - 25 + EPS > 0)
                    ans += (DD - P[P.size() - 1] - 25 + EPS) / 50 + 1;
            } else {
                ans = (DD + EPS) / 50 + 1;
            }
            total += ans;
        }
        cout << "Map " << ++times << endl;
        cout << "Trees = " << total << endl;
    }
    return 0;
}
