#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
 
int SIGN(double x) { 
    return (x > EPS) - (x < -EPS);
}
 
struct P {
    double x, y;
    P(double a = 0.0, double b = 0.0) : x(a), y(b) {}
    P operator + (const P &a) { return P(x + a.x, y + a.y); }
    P operator - (const P &a) { return P(x - a.x, y - a.y); }
    P operator * (const double a) { return P(x * a, y * a); }
    double operator * (const P &a) { return x * a.x + y * a.y; }
    double operator ^ (const P &a) { return x * a.y - y * a.x; }
    void in() { cin >> x >> y; }
    double L() { return sqrt(x * x + y * y); }
    P T() {return P(-y,x); }
};

struct CCL {
    P o;
    double r;
    CCL(P a = P(), double v = 0.0) :o(a), r(v) {}
    void in() { o.in(); cin >> r; }
    void out() { printf("%.10lf %.10lf %.10lf\n", o.x, o.y, fabs(r)); }
    P get(double theta) { return o + P(r * cos(theta),r * sin(theta)); }
};
 
CCL c[7];
P p;
 
CCL change(CCL a) {
    double x = 1.0 / ((a.o - p).L() - a.r);
    double y = 1.0 / ((a.o - p).L() + a.r);
    CCL s;
    s.r = (x - y) / 2;
    x = (x + y) / 2;
    y = (a.o - p).L();
    s.o = p + (a.o - p) * (x / y);
    return s;
}
 
int add(P a, P b, int &k) {
    double d = (b - a) ^ (p - a);
    d /= (b - a).L();
    d = fabs(d);
    if (d > 10 * EPS) {
       double w = 1 / d / 2;
       P n = (b - a).T();
       P a1 = p + n * (w / n.L());
       P b1 = p - n * (w / n.L());
       if (fabs((a1 - a) ^ (b - a)) < fabs((b - a) ^ (b1 - a)))
            c[k++] = CCL(a1, w);
       else
            c[k++] = CCL(b1, w);
    }
    return 0;
}

int solve() {
    c[0] = change(c[0]);
    c[1] = change(c[1]);

    if (c[1].r > c[0].r) swap(c[0], c[1]);
    P v = c[1].o - c[0].o;
    double base = atan2(v.y, v.x);
    double theta = acos((c[0].r - c[1].r) / v.L());
 
    P a, b;
    int k = 2;
    a = c[0].get(base + theta);
    b = c[1].get(base + theta);
    
    if (SIGN((c[0].o - a) ^ (b - a)) == SIGN((p - a) ^ (b - a)) &&
        SIGN((c[1].o - a) ^ (b - a)) == SIGN((p - a) ^ (b - a))) add(a, b, k);

    a = c[0].get(base - theta);
    b = c[1].get(base - theta);
 
    if (SIGN((c[0].o - a) ^ (b - a)) == SIGN((p - a) ^ (b - a)) &&
        SIGN((c[1].o - a) ^ (b - a)) == SIGN((p - a) ^ (b - a))) add(a, b, k);
   
    return k - 2;
}
 
int main() {
    int times;
    cin >> times;
    while (times--) {
        c[0].in();
        c[1].in();
        p.in();
        int k = solve();
        cout << k << endl;
        for (int i = 0; i < k; ++i) c[2 + i].out();
    }
    return 0;
}
