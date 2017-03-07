#include <iostream>
#include <deque>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const double INF = 1e100;

struct node {
    int w;
    double t, dt;
    bool operator < (const node &B) const {
        return t > B.t;
    }
};

vector<node> D, C;

int N, M;
double f[MAXN], g[MAXN];

bool isinff(double a) {
    return a < -INF / 2;
}

double intersect(pair<double, double> A, pair<double, double> B) {
    return (A.first - B.first) / (B.second - A.second);
}

void discrete() {
    for (int i = 0; i <= M; ++i) f[i] = -INF;
    f[0] = 0;

    for (int i = 0; i < D.size(); ++i) {
        int w = D[i].w;
        double t = D[i].t, dt = D[i].dt;
        if (dt == 0) {
            for (int j = 0; j + w <= M; ++j) f[j + w] = max(f[j + w], f[j] + t);
            continue;
        }

        for (int j = 0; j < w; ++j) {
            deque<pair<double, double> > Q;
            if (!isinff(f[j])) Q.push_back(make_pair(f[j], 0));
            for (int k = 1; j + k * w <= M; ++k) {
                while (Q.size() > 1) {
                    if (Q[0].first + Q[0].second * k >= Q[1].first + Q[1].second * k) break;
                    Q.pop_front();
                }
                pair<double, double> newq = make_pair(f[j + k * w] - k * t - k * (k + 1) / 2 * dt, k * dt);
                if (!Q.empty()) f[j + k * w] = max(f[j + k * w], k * t - k * (k - 1) / 2 * dt + Q[0].first + k * Q[0].second);
                if (isinff(newq.first)) continue;

                int S = Q.size();
                while (S > 1) {
                    if (intersect(Q[S - 1], Q[S - 2]) < intersect(Q[S - 1], newq)) break;
                    Q.pop_back();
                    --S;
                }
                Q.push_back(newq);
            }


        }
    }
}

void continuous() {
    for (int i = 0; i <= M; ++i) g[i] = -INF;
    g[0] = 0;

    if (C.size() == 0) return ;
    sort(C.begin(), C.end());

    double t = C[0].t, dt = C[0].dt, w = 0, temp = 0;
    int ww = 0;
    if (dt == 0) {
        for (int i = 1; i <= M; ++i) g[i] = t * i;
        return ;
    }

    for (int i = 1; i < C.size(); ++i) {
        if (C[i].t == t) {
            if (C[i].dt == 0) {
                ++ww;
                temp += (ww - w) * t;
                g[ww] = g[ww - 1] + temp;
                for (int i = ww + 1; i <= M; ++i) g[i] = g[i - 1] + t;
                return ;
            }
            dt = dt * C[i].dt / (dt + C[i].dt);
            continue;
        }
        double neww = (t - C[i].t) / dt + w;
        if (ww + 1 > neww) {
            temp += (C[i].t + t) * (neww - w) / 2;
            w = neww;
            t = C[i].t;
            --i;
            continue;
        }
        while (ww + 1 <= neww) {
            ++ww;
            double L = ww - w;
            temp += (t + t - dt * L) * L / 2;
            t -= dt * L;
            w = ww;
            g[ww] = g[ww - 1] + temp;
            temp = 0;
        }
        temp += (t + C[i].t) * (neww - ww) / 2;
        t = C[i].t;
        w = neww;
        --i;
    }
    while (ww < M) {
        ++ww;
        double L = ww - w;
        temp += (t + t - dt * L) * L / 2;
        t -= dt * L;
        w = ww;
        g[ww] = g[ww - 1] + temp;
        temp = 0;
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        char type;
        node X;
        cin >> type;
        if (type == 'D') {
            cin >> X.w >> X.t >> X.dt;
            D.push_back(X);
        } else {
            cin >> X.t >> X.dt;
            C.push_back(X);
        }
    }
    discrete();
    continuous();

    double ans = -INF;
    for (int i = 0; i <= M; ++i) ans = max(ans, f[i] + g[M - i]);
    if (isinff(ans))
        cout << "impossible" << endl;
    else 
        cout << fixed << setprecision(8) << ans << endl;

    return 0;
}
