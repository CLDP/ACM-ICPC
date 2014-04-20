#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 30;

struct poly{
   double c[MAXN];
   double value(double x) {
       double ans = 0;
       for(int i = MAXN - 1; i >= 0; --i) ans = ans * x + c[i];
        return ans;
    }
    poly operator * (const poly &p) {
        poly t;
        for (int i = 0; i < MAXN; ++i)
         for (int j = 0; j <= i; ++j) t.c[i] += p.c[i - j] * c[j];
        return t;
    }
    double integral(double a, double b) {
        poly t;
        for (int i = 1; i < MAXN; ++i) t.c[i] = c[i - 1] / i;
        return t.value(b) - t.value(a);
    }
    void clear() {
        memset(c, 0, sizeof(c));
    }
    poly(){
        memset(c, 0, sizeof(c));
    }
};


int main(){
    double c;
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        poly p;
        for (int i = N; i >= 0; --i) cin >> p.c[i];
        cin >> c;
        poly q;
        q.c[1] = 1, q.c[0] = -c;                 
        double A = p.integral(-1, c);
        double B = q.integral(-1, c);
        double C = (p * q).integral(-1, c);
        double D = (q * q).integral(-1, c);
        double E = p.integral(c, 1);
        double F = q.integral(c, 1);
        double G = (p * q).integral(c, 1);
        double H = (q * q).integral(c, 1);
        double I = 2 * (A + E - B * C / D - F * G / H);
        double a1 = (C - I * B) / D;
        double a0 = I - c * a1;
        double b1 = (G - I * F) / H;
        double b0 = I - c * b1;
        printf("Case %d: %.3lf %.3lf %.3lf %.3lf\n", ++times, a1, a0, b1, b0);
    }
    return 0;
}
