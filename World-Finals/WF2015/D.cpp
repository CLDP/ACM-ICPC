#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double PI = acos(-1.0);
const double EPS = 1e-8;

struct circle {
    double r, x, y, z;
};

int N, M;
circle cs[MAXN];

double cal(double L, double R) {
    double ans = R - L;
    ans *= 1e10;
    for (int i = 0; i < N; ++i) {
        double up = max(min(R - cs[i].z, cs[i].r), -cs[i].r);
        double low = min(max(L - cs[i].z, -cs[i].r), cs[i].r);
        ans -= PI * cs[i].r * cs[i].r * (up - low);
        ans += PI * up * up * up / 3;
        ans -= PI * low * low * low / 3;
    }
    return ans;
}

int main() {
    cin >> N >> M;
    double sum = 1e15;
    for (int i = 0; i < N; ++i) {
        cin >> cs[i].r >> cs[i].x >> cs[i].y >> cs[i].z;
        sum -= 4 * PI * cs[i].r * cs[i].r * cs[i].r / 3;
    }
    
    double one = sum / M;
    vector<double> ans(1, 0);
    for (int i = 0; i < M; ++i) {
        double L = ans.back(), R = 100000;
        while (L + EPS < R) {
            double mid = (L + R) / 2;
            if (cal(ans.back(), mid) < one)
                L = mid;
            else
                R = mid;
        }
        ans.push_back(L);
    }
    
    for (int i = 1; i <= M; ++i)
        printf("%.9lf\n", (ans[i] - ans[i - 1]) / 1000);
    
    return 0;
}
