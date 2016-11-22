#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <iostream>
#include <algorithm>
#define X first
#define Y second
using namespace std;

const int MAXN = 300110;
const int MAXM = 900110;
const double PI = acos(-1.0);
const double EPS = 1e-9;

typedef pair<double, double> point;

point a[MAXM][3];
int N;
pair<int, int> b[MAXM];
int f[MAXN], d[MAXN];
double tmp;

struct node {
    double p, v;
    int t, pos;
    bool operator == (const node &x) {
        return x.t == t && x.pos == pos;
    }
    double value() {
        return p + v * tmp;
    }
};

bool operator < (const node &y, const node &x) {
    return y.p + y.v * tmp < x.p + x.v * tmp - EPS 
        || (fabs(y.p + y.v * tmp - x.p - x.v * tmp) < EPS && y.t < x.t);
}

bool equal(double x, double y) {
    return fabs(x - y) < EPS;
}

bool cmp(const point &a, const point &b) {
    return a.X * 1e10 + a.Y < b.X * 1e10 + b.Y;
}

bool cmp2(const pair<int, int> &x, const pair<int, int> &y) {
    return a[x.X][x.Y].X < a[y.X][y.Y].X;
}

int rorate(point &a, double alpha) {
    double x, y;
    x = a.X * cos(alpha) - a.Y * sin(alpha);
    y = a.X * sin(alpha) + a.Y * cos(alpha);
    a.X = x;
    a.Y = y;
    return 0;
}

int getf(int p) {
    if (p == -1) return 1;
    if (d[p] != -1) return d[p];
    return d[p] = getf(f[p]) + 1;
}

int main() {
    int times = 0;
    while (cin >> N) {
        if (N == -1) break;
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < 3; ++j) cin >> a[i][j].X >> a[i][j].Y;
        double alpha = 0.782346 * PI;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 3; ++j) rorate(a[i][j], alpha);
            sort(a[i], a[i] + 3, cmp);
            b[3 * i].X = b[3 * i + 1].X = b[3 * i + 2].X = i;
            b[3 * i].Y = 0;
            b[3 * i + 1].Y = 1;
            b[3 * i + 2].Y = 2;
        }
        sort(b, b + 3 * N, cmp2);
        
        set<node> T;
        bool flag = true;
        memset(f, 0xff, sizeof(f));
        
        node t1, t2, t3;
        for (int i = 0; flag && i < 3 * N; ++i) {
            int j = b[i].X;
            int k = b[i].Y;
            tmp = a[j][k].X;
            if (k == 0) {
                t1.v = (a[j][1].Y - a[j][0].Y) / (a[j][1].X - a[j][0].X);
                t1.p = a[j][0].Y - a[j][0].X * t1.v;
                t2.v = (a[j][2].Y - a[j][0].Y) / (a[j][2].X - a[j][0].X);
                t2.p = a[j][0].Y - a[j][0].X * t2.v;
                t1.pos = t2.pos = j;
                if (t1.v > t2.v) swap(t1, t2);
                t1.t = 0;
                t2.t = 1;
                set<node>::iterator iter = T.lower_bound(t1);
                t3 = *iter;
                if ((iter != T.end()) && equal(t3.value(), t1.value())) {
                    flag = false;
                    break;
                }
                T.insert(t1);
                T.insert(t2);
                iter = T.find(t1);
                if (iter == T.end()) {
                    flag = false;
                    break;
                }
                if (iter != T.begin()) {
                    --iter;
                    if (iter->t == 1)
                        f[j] = f[iter->pos];
                    else
                        f[j] = iter->pos;
                }
            } else 
            if (k == 1) {
                int l;
                if ((a[j][1].Y - a[j][0].Y) / (a[j][1].X - a[j][0].X)
                  < (a[j][2].Y - a[j][0].Y) / (a[j][2].X - a[j][0].X))
                    l = 0;
                else
                    l = 1;
                t1.v = (a[j][1].Y - a[j][0].Y) / (a[j][1].X - a[j][0].X);
                t1.p = a[j][0].Y - a[j][0].X * t1.v;
                t1.pos = j;
                t1.t = l;
                double td = t1.value();
                set<node>::iterator iter = T.find(t1);
                if (iter == T.end()) {
                    flag = false;
                    break;
                }
                if (iter != T.begin()) {
                    --iter;
                    t3 = *iter;
                    if (td <= t3.value() + EPS) {
                        flag = false;
                        break;
                    }
                    ++iter;
                }
                ++iter;
                if (iter != T.end()) {
                    t3 = *iter;
                    if (td >= t3.value() - EPS) {
                        flag = false;
                        break;
                    }
                }
                T.erase(t1);
                t1.v = (a[j][2].Y - a[j][1].Y) / (a[j][2].X - a[j][1].X);
                t1.p = a[j][1].Y - a[j][1].X * t1.v;
                T.insert(t1);
            } else {
                if ((a[j][1].Y - a[j][0].Y) / (a[j][1].X - a[j][0].X)
                 >= (a[j][2].Y - a[j][0].Y) / (a[j][2].X - a[j][0].X)) {
                    t1.v = (a[j][2].Y - a[j][0].Y) / (a[j][2].X - a[j][0].X);
                    t1.p = a[j][0].Y - a[j][0].X * t1.v;
                } else {
                    t1.v = (a[j][2].Y - a[j][1].Y) / (a[j][2].X - a[j][1].X);
                    t1.p = a[j][1].Y - a[j][1].X * t1.v;
                }
                t1.pos = j;
                t1.t = 0;
                set<node>::iterator iter2 = T.find(t1);
                set<node>::iterator iter1 = iter2++;
                if (iter1 == T.end() || iter2 == T.end() || iter2->pos != j || iter2->t != 1) {
                    flag = false;
                    break;
                }
                double td = t1.value();
                set<node>::iterator iter3 = iter2++;
                T.erase(iter3);
                if (iter2 != T.end()) {
                    t3 = *iter2;
                    if (t3.value() <= EPS + td) {
                        flag = false;
                        break;
                    }
                }
                iter3 = iter1--;
                if (iter3 != T.begin()) {
                    t3 = *iter1;
                    if (t3.value() >= td - EPS) {
                        flag = false;
                        break;
                    }
                }
                T.erase(iter3);
            }
        }
        
        cout << "Case " << ++times << ": ";
        if (!flag) {
            cout << "ERROR" << endl;
            continue;
        }
        int ans = 1;
        memset(d, 0xff, sizeof(d));
        for (int i = 0; i < N; ++i) ans = max(ans, getf(i));
        cout << ans << " shades" << endl;
    }
    return 0;
}
