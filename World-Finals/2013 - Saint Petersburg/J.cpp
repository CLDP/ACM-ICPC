#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const double ZERO = 1e-8;
const double PI = acos(-1.0);

int Sign(double x) {
    if (x > ZERO) return 1;
    return x < -ZERO ? -1 : 0;
}

struct Point {
    double x, y;
    Point() {x = y = 0;}
    Point(double a, double b) {x = a, y = b;}
    inline Point operator - (const Point &b) const {return Point(x - b.x, y - b.y);}
    inline Point operator + (const Point &b) const {return Point(x + b.x, y + b.y);}
    inline Point operator * (const double &b) const {return Point(x * b, y * b);}
    inline double dot(const Point &b) const {return x * b.x + y * b.y;}
    inline double cross(const Point &b, const Point &c) const {
        return (b.x - x) * (c.y - y) - (c.x - x) * (b.y - y);
    }
    inline double Dis(const Point &b) const {return sqrt((*this - b).dot(*this - b));}
    // Three point, same line
    inline bool InLine(const Point &b, const Point &c) const {return !Sign(cross(b, c));}
    // Point on seg, include boundary
    inline bool OnSeg(const Point &b, const Point &c) const {
        return InLine(b, c) && (*this - c).dot(*this - b) < ZERO;
    }
};

inline double Sqr(const Point &p) {return p.dot(p);}

Point LineCross(const Point &a, const Point &b, const Point &c, const Point &d) {
    double u = a.cross(b, c), v = b.cross(a, d);
    return Point((c.x * v + d.x * u) / (u + v), (c.y * v + d.y * u) / (u + v));
}

double LineCrossCircle(const Point &a, const Point &b, const Point &r, 
            double R, Point &p1, Point &p2) {
    Point fp = LineCross(r, Point(r.x + a.y - b.y, r.y + b.x - a.x), a, b);
    double rtol = r.Dis(fp);
    double rtos = fp.OnSeg(a, b) ? rtol : min(r.Dis(a), r.Dis(b));
    double atob = a.Dis(b);
    double fptoe = sqrt(R * R - rtol * rtol) / atob;
    if(rtos > R - ZERO) return rtos;
    p1 = fp + (a - b) * fptoe;
    p2 = fp + (b - a) * fptoe;
    return rtos;
}


double SectorArea(const Point &r, const Point &a, const Point &b, double R) {
    // Sector Area for no more than 180 degree, r->a->b counterclockwise
    double A2 = Sqr(r - a), B2 = Sqr(r - b), C2 = Sqr(a - b);
    return R * R * acos((A2 + B2 - C2) * 0.5 / sqrt(A2) / sqrt(B2)) * 0.5;
}


double TACIA(const Point &r, const Point &a, const Point &b, double R) {
    // Triangle And Circle Intersect Area, counterclockwise, r is center
    double adis = r.Dis(a), bdis = r.Dis(b);
    if (adis < R + ZERO && bdis < R + ZERO) return r.cross(a, b) * 0.5;
    Point ta, tb;
    if (r.InLine(a, b)) return 0;
    double rtos = LineCrossCircle(a, b, r, R, ta, tb);
    if (rtos > R - ZERO) return SectorArea(r, a, b, R);
    if (adis < R + ZERO) return r.cross(a, tb) * 0.5 + SectorArea(r, tb, b, R);
    if (bdis < R + ZERO) return r.cross(ta, b) * 0.5 + SectorArea(r, a, ta, R);
    return r.cross(ta, tb) * 0.5 + SectorArea(r, a, ta, R) + SectorArea(r, tb, b, R);
}


double SPICA(int n, Point r, double R) {
    // Simple Polygon Intersect Circle Area
    Point ori, p[2];
    cin >> ori.x >> ori.y;
    p[0] = ori;
    double res = 0, if_clock_t;
    for (int i = 1; i <= n; ++i) {
        if (i == n) 
            p[i & 1] = ori;
        else
            cin >> p[i & 1].x >> p[i & 1].y;
        if_clock_t = Sign(r.cross(p[~i & 1], p[i & 1]));
        if (if_clock_t < 0) 
            res -= TACIA(r, p[i & 1], p[~i & 1], R);
        else
            res += TACIA(r, p[~i & 1], p[i & 1], R);
    }
    return fabs(res);
}


Point center;
int n;
double R;


int main() {
    cin >> n >> R;
    center = Point(0, 0);
    printf("%.6f\n", SPICA(n, center, R));
    return 0;
}
