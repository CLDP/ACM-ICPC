const double EPS = 1e-8;
const double PI = acos(-1.0);

double F(double x) {
    return sin(x);
}

double simpson(double a, double b) {
    double c = a + (b - a) / 2;
    return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}

// adaptive Simpson's rule, calculate integration
double asr(double a, double b, double EPS, double A) {
    double c = a + (b - a) / 2;
    double L = simpson(a, c), R = simpson(c, b);
    if (fabs(L + R - A) <= 15 * EPS) return L + R + (L + R - A) / 15.0;
    return asr(a, c, EPS, L) + asr(c, b, EPS, R);
}

int main () {
    printf("%.16lf\n", asr(0, PI, 1e-10, simpson(0, PI)));
    return 0;
}

