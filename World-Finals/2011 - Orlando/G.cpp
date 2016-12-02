#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-6;

int N;
int L[510];


bool getT(int A, int B, int N, int a, double mid, bool flag) {
    double theta = 0;
    for (int i = A; i <= B; ++i) 
     if (i != a) theta += 2 * asin(1.0 * L[i] / (2 * mid));
    double alpha = 2 * asin(L[a] / (2 * mid));
    if (flag) return theta + alpha <= 2 * PI; else return theta > alpha;
}

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double deal(int A, int B) {
    if (A + 2 > B) return 0;
    int N = B - A + 1;
    int a = A;
    for (int i = A + 1; i <= B; ++i) 
     if (L[i] > L[a]) a = i;
    
    int sum = 0;
    for (int i = A; i <= B; ++i) sum += L[i];
    
    if (sum <= 2 * L[a]) return deal(A, a - 1) + deal(a + 1, B);
    double theta = 0;
    for (int i = A; i <= B; ++i) theta += 2 * asin(1.0 * L[i] / L[a]);
    bool flag = theta >= 2 * PI;
    
    double LL = L[a] * 0.5, RR = 1e10;
    while (LL + 1e-8 < RR) {
        double mid = (LL + RR) / 2;
        if (getT(A, B, N, a, mid, flag)) RR = mid; else LL = mid;
    }
    
    vector<pair<double, double> > P;
    
    theta = 0;
    for (int i = A; i <= B; ++i) {
        if (!flag && i == a) {
            theta += 2 * PI - 2 * asin(1.0 * L[i] / (2 * RR));
        } else {
            theta += 2 * asin(1.0 * L[i] / (2 * RR));
        }
        P.push_back(make_pair(RR * cos(theta), RR * sin(theta)));
    }
    
    double ans = 0;
    N = P.size();
    for (int i = 0; i < N - 2; ++i) {
        ans += cross(P[i + 1].first - RR, P[i + 1].second, P[i].first - RR, P[i].second);
    }
    
    return max(fabs(ans) / 2, deal(A, a - 1) + deal(a + 1, B));
}



int main() {
    int times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        for (int i = 0; i < N; ++i) cin >> L[i];
        printf("Case %d: %.6lf\n", ++times, deal(0, N - 1));
    }
    return 0;
}
