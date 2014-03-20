#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 60;
const int INF = 1000000000;

struct line {
    int a, b, c;
};

int N, M, T, Q;
vector<pair<double, double> > X, Y;
int d[MAXN][MAXN];



double dist(double a, double b, double c, double d) {
    return (a - c) * (a - c) + (b - d) * (b - d);
}

bool check(double xx, double yy, int i) {
    double now = dist(xx, yy, X[i].first, X[i].second);
    for (int j = 1; j <= N; ++j) {
        if (i == j) continue;
        if (dist(xx, yy, X[j].first, X[j].second) < now) return false;
    }
    return true;
}

bool between(double a, double s, double t) {
    if (s > t) swap(s, t);
    return s <= a && a <= t;
}

int change(double xs, double ys, double xt, double yt) {
    double A, B, C;
    A = yt - ys;
    B = xs - xt;
    C = - xs * yt + ys * xt;
    
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        double C2 = B * X[i].first - A * X[i].second;
        double yy = (- B * C - A * C2) / (A * A + B * B);
        double xx = (B * C2 - A * C) / (A * A + B * B);
        if (between(xx, xs, xt) && between(yy, ys, yt)) {
            if (check(xx, yy, i)) ++ans;
        } else {
            if (check(xs, ys, i) || check(xt, yt, i)) ++ans;
        }
    }
    return ans - 1;
}


int main() {
    int times = 0;
    while (cin >> N >> M >> T >> Q) {
        if (N + M + T + Q == 0) break;
        X = vector<pair<double, double> >(N + 1);
        Y = vector<pair<double, double> >(M + 1);
        for (int i = 1; i <= N; ++i) cin >> X[i].first >> X[i].second;
        for (int i = 1; i <= M; ++i) cin >> Y[i].first >> Y[i].second;
        
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) d[i][j] = INF;
         
        int a, b, c;
        for (int i = 0; i < T; ++i) {
            cin >> a >> b;
            c = change(Y[a].first, Y[a].second, Y[b].first, Y[b].second);
            d[a][b] = d[b][a] = c;
        }
        for (int k = 1; k <= N; ++k)
         for (int i = 1; i <= N; ++i)
          for (int j = 1; j <= N; ++j)
           if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
        
        cout << "Case " << ++times << ":" << endl;
        for (int i = 0; i < Q; ++i) {
            cin >> a >> b;
            if (d[a][b] == INF) cout << "Impossible" << endl; else cout << d[a][b] << endl;
        }
        
    }
    return 0;
}
