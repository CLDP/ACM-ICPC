#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 10010;
const double PI = acos(-1.0);

int N, M;
double alpha;
pair<int, int> x[MAXN];
double p[MAXN], q[MAXN];
double y[MAXN];
int RR[MAXN];

bool check(int R, double L, double H, double &NL) {
    double k = alpha, b = -alpha * L + H;
    double k2 = (q[R + 1] - q[R]) / (p[R + 1] - p[R]), b2 = -k2 * p[R] + q[R];
    if (fabs(k - k2) < 1e-7) return false;
    double xx = (b2 - b) / (k - k2);
    NL = xx;
    return p[R] <= xx && xx <= p[R + 1];
}

int main() {
    freopen("green.in", "r", stdin);
    freopen("green.out", "w", stdout);
    cin >> N >> M >> alpha;
    for (int i = 0; i < N; ++i) {
        cin >> x[i].first;
        x[i].second = i;
    }
    
    alpha = -tan(alpha / 180 * PI);
    sort(x, x + N);
    for (int i = 0; i < M; ++i) cin >> p[i] >> q[i];
    
    int R = 0, i;
    double L = p[0], ans = 0;
    for (i = 0; i < N; ++i) {
        y[x[i].second] = L;
        RR[x[i].second] = R;
        ans += x[i].first;
        double H = (q[R + 1] - q[R]) / (p[R + 1] - p[R]) * (L - p[R]) + q[R];
        double NL;
        while (R < M - 1 && !check(R, L, H + x[i].first, NL)) ++R;
        if (NL > p[M - 1]) break;
        L = NL;
    }
    
    if (i < N - 1) {
        int j = x[i].second;
        double H = (q[RR[j] + 1] - q[RR[j]]) / (p[RR[j] + 1] - p[RR[j]]) * (L - p[RR[j]]) + q[RR[j]];
        double k = alpha, b = -alpha * y[j] + x[i].first + H;
        double MA = 0;
        int pp = M - 1;
        for (int t = RR[j] + 1; t < M; ++t) {
            H = k * p[t] + b;
            if (x[N - 1].first + q[t] - H > MA) {
                MA = x[N - 1].first + q[t] - H;
                pp = t;
            }
        }
        ans += MA;
        for (i = i + 1; i < N; ++i) y[x[i].second] = p[pp];
    }
    
    cout.precision(15);
    cout << ans << endl;
    for (int i = 0; i < N; ++i) cout << y[i] << endl;
    
    
    return 0;
}
