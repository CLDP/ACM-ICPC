#include <vector>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 22;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int N;
double x[MAXN], y[MAXN], r[MAXN];
bool mark[MAXN];
double dc[MAXN][MAXN], arg[MAXN][MAXN], len[MAXN][MAXN];
double xi[MAXN][MAXN], yi[MAXN][MAXN], xj[MAXN][MAXN], yj[MAXN][MAXN];
double cur, ans;
double pxa[MAXN], pya[MAXN], pxb[MAXN], pyb[MAXN];


double dis(double x, double y) {
    return sqrt(x * x + y * y);
}

double angle(double x, double y) {
    if (y > 0) return acos(x / dis(x, y));
    if (y < 0) return 2 * PI - acos(x / dis(x, y));
    if (x > 0) return 0;
    return PI;
}

int cross(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd) {
    double cra = (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya);
    double crb = (xb - xa) * (yd - ya) - (xd - xa) * (yb - ya);
    if (cra * crb > -EPS) return 0;
    cra = (xd - xc) * (ya - yc) - (xa - xc) * (yd - yc);
    crb = (xd - xc) * (yb - yc) - (xb - xc) * (yd - yc);
    if (cra * crb > -EPS) return 0;
    return 1;
}

int go(int nn, int v, double a, int T) {
    for (int j = 0; j < N; ++j)
     if (mark[j] && len[v][j] > 0) {
         int k;
         for (k = 0; k < nn; ++k)
          if (cross(pxa[k], pya[k], pxb[k], pyb[k], xi[v][j], yi[v][j], xj[v][j], yj[v][j])) break;
         if (k < nn) continue;
         
         pxa[nn] = xi[v][j];
         pya[nn] = yi[v][j];
         pxb[nn] = xj[v][j];
         pyb[nn] = yj[v][j];
         
         double add = len[v][j];
         if (a > -1) {
             if (r[v] < 0) {
                 if (arg[v][j] > a - EPS)
                     add -= r[v] * (arg[v][j] - a);
                 else
                     add -= r[v] * (2 * PI + arg[v][j] - a);
             } else {
                 if (a > arg[v][j] - EPS)
                     add += r[v] * (a - arg[v][j]);
                 else
                     add += r[v] * (2 * PI + a - arg[v][j]);
             }
         }
         mark[j] = 0;
         cur += add;
         if (cur < ans) {
             if (j == T)
                 ans = cur;
             else
                 go(nn + 1, j, arg[v][j], T);
         }
         cur -= add;
         mark[j] = 1;
     }
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) {
            string dir;
            cin >> x[i] >> y[i] >> r[i] >> dir;
            if (dir == "CC") r[i] = -r[i];
            mark[i] = 1;
        }
        int S, T;
        double D;
        cin >> S >> T >> D;
        
        mark[S] = 0;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j)
          dc[i][j] = dis(x[j] - x[i], y[j] - y[i]);
          
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) {
             if (i == j) continue;
             arg[i][j] = angle(x[j] - x[i], y[j] - y[i]) + acos((r[i] - r[j]) / dc[i][j]);
             if (arg[i][j] >= 2 * PI) arg[i][j] -= 2 * PI;
             if (arg[i][j] < 0) arg[i][j] += 2 * PI;
             len[i][j] = sqrt(dc[i][j] * dc[i][j] - (r[j] - r[i]) * (r[j] - r[i]));
             if (len[i][j] >= D) {
                 len[i][j] = -1;
             } else {
                 xi[i][j] = x[i] + r[i] * cos(arg[i][j]);
                 yi[i][j] = y[i] + r[i] * sin(arg[i][j]);
                 xj[i][j] = x[j] + r[j] * cos(arg[i][j]);
                 yj[i][j] = y[j] + r[j] * sin(arg[i][j]);
                 for (int k = 0; k < N; ++k) {
                     if (k == i || k == j) continue;
                     if ((xj[i][j] - xi[i][j]) * (x[k] - xi[i][j]) 
                       + (yj[i][j] - yi[i][j]) * (y[k] - yi[i][j]) <= 0) continue;
                     if ((xi[i][j] - xj[i][j]) * (x[k] - xj[i][j]) 
                       + (yi[i][j] - yj[i][j]) * (y[k] - yj[i][j]) <= 0) continue;
                     if (fabs((xj[i][j] - xi[i][j]) * (y[k] - yi[i][j]) 
                            - (yj[i][j] - yi[i][j]) * (x[k] - xi[i][j])) / len[i][j] > fabs(r[k]) + EPS) continue;
                     len[i][j] = -1;
                     break;
                 }
             }
         }
        
        cur = 0;
        ans = 1e10;
        go(0, S, -2, T);
        if (S == T) ans = 0;
        
        printf("Case %d: ", ++times);
        if (ans < 1e10) {
            printf("length = %.2lf\n", ans);
        } else {
            printf("Cannot reach destination shaft\n");
        }
    }
    return 0;
}

