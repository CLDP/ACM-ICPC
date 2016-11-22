#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

struct Point { double x, y; };
double sqr(double x) { return x * x; }
int dcmp(double x) {
    if (x < -EPS) return -1; else return (x > EPS);
}
double cross(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
double dot(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
}
double dissqr(Point p1, Point p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}
double dis(Point p1, Point p2) {
    return sqrt(dissqr(p1, p2));
}
int PointEqual(const Point &p1, const Point &p2) {
    return dcmp(p1.x - p2.x) == 0 && dcmp(p1.y - p2.y) == 0;
}

Point bp;  // Used for GrahamScan, lowest point

bool PolarCmp(const Point &p1, const Point &p2) {
    int u = dcmp(cross(bp, p1, p2));
    return u > 0 || (u == 0 && dcmp(dissqr(bp, p1) - dissqr(bp, p2)) < 0);
}
int GrahamScan(Point ch[], int n, int &m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int u = dcmp(ch[i].x - ch[k].x);
        int v = dcmp(ch[i].y - ch[k].y);
        if (v < 0 || (v == 0 && u < 0)) k = i;
    }
    bp = ch[k];
    sort(ch, ch + n, PolarCmp);
    n = unique(ch, ch + n, PointEqual) - ch;
    if (n <= 1) {
        m = n;
        return 0;
    }
    if (dcmp(cross(ch[0], ch[1], ch[n - 1])) == 0) {
        m = 2;
        ch[1] = ch[n - 1];
        return 0;
    }
    ch[n++] = ch[0];
    int i = 1;
    for (int j = 2; j < n; ++j) {
        while (i > 0 && dcmp(cross(ch[i - 1], ch[i], ch[j])) < 0) --i;
        ch[++i] = ch[j];
    }
    m = i;
    return 0; 
}

int N;
Point X[10];
Point ch[MAXN];
double L[2000];
double f[2000];

double dp(int S) {
    if (f[S] > 0) return f[S];
    f[S] = L[S];
    if (__builtin_popcount(S) == 1) return f[S];
    for (int i = 0; i < (1 << N); ++i) {
        if ((i | S) != S) continue;
        if (i == S) continue;
        f[S] = min(f[S], dp(S - i) + dp(i));
    }
    return f[S];
}

int main() {
    int times = 0;
    double R;
    while (cin >> N >> R) {
        if (N == 0) break;
        memset(L, 0, sizeof(L));
        for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y;
        for (int i = 1; i < (1 << N); ++i) {
            int n = 0, m = 0;
            for (int j = 0; j < N; ++j) {
                if (i & (1 << j)) ch[n++] = X[j];
            }
            if (n == 1) {
                L[i] = 2 * PI * R;
            } else 
            if (n == 2) {
                L[i] = 2 * PI * R;
                L[i] += 2 * dis(ch[0], ch[1]);
            } else {
                GrahamScan(ch, n, m);
                for (int j = 0; j < m - 1; ++j) L[i] += dis(ch[j], ch[j + 1]);
                L[i] += dis(ch[m - 1], ch[0]);
                L[i] += 2 * PI * R;
            }
        }
        memset(f, 0, sizeof(f));
        printf("Case %d: length = %.2lf\n", ++times, dp((1 << N) - 1));
    }
    return 0;
}
