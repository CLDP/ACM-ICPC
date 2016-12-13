const double PI = acos(-1.0);
const double EPS = 1e-15;

int dcmp(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

// cube root
double cbrt(double x) {
    if (x > EPS)  return  pow( x, 1 / 3.0);
    if (x < -EPS) return -pow(-x, 1 / 3.0);
    return 0;
}

// c0 + c1x + c2x^2 = 0
// return number of distinct non-complex roots
int solve_quadric(double c[3], double s[2]) {
    double p = c[1] / (2 * c[2]);
    double q = c[0] / c[2];
    double d = p * p - q;
    if (dcmp(d) == 0) {
        s[0] = -p;
        return 1;
    }
    if (dcmp(d) < 0) return 0;
    d = sqrt(d);
    s[0] = -p + d;
    s[1] = -p - d;
    return 2;
}

// c0 + c1x + c2x^2 + c3x^3 = 0
// return number of distinct non-complex roots
// The answers are not very precise
int solve_cubic(double c[4], double s[3]) {
    int num = 0;
    double A = c[2] / c[3];
    double B = c[1] / c[3];
    double C = c[0] / c[3];
    double sqa = A * A;
    double p = 1.0 / 3 * (-1.0 / 3 * sqa + B);
    double q = 1.0 / 2 * (2.0 / 27 * A * sqa - 1.0 / 3 * A * B + C);
    double cbp = p * p * p;
    double d = q * q + cbp;
    if (dcmp(d) == 0) {
        if (dcmp(q) == 0) {
            s[0] = 0;
            num = 1;
        } else {
            double u = cbrt(-q);
            s[0] = 2 * u;
            s[1] = -u;
            num = 2;
        }
    } else
    if (dcmp(d) < 0) {
        double phi = 1.0 / 3 * acos(-q / sqrt(-cbp));
        double t = 2 * sqrt(-p);
        s[0] = t * cos(phi);
        s[1] = -t * cos(phi + PI / 3);
        s[2] = -t * cos(phi - PI / 3);
        num = 3;
    } else {
        d = sqrt(d);
        double u = cbrt(d - q);
        double v = -cbrt(d + q);
        s[0] = u + v;
        num = 1;
    }
    double sub = 1.0 / 3 * A;
    for (int i = 0; i < num; ++i) s[i] -= sub;
    return num;
}

// c0 + c1x + c2x^2 + c3x^3 + c4x^4 = 0
// return number of distinct non-complex roots
// If there are multiply same roots, though roots are correct,
// the number returned is not guaranteed to be correct
// The answers are not very precise
int solve_quartic(double c[5], double s[4]) {
    int num = 0;
    double A = c[3] / c[4];
    double B = c[2] / c[4];
    double C = c[1] / c[4];
    double D = c[0] / c[4];
    double sqa = A * A;
    double p = -3.0 / 8 * sqa + B;
    double q = 1.0 / 8 * sqa * A - 1.0 / 2 * A * B + C;
    double r = -3.0 / 256 * sqa * sqa + 1.0 / 16 * sqa * B - 1.0 / 4 * A * C + D;
    if (dcmp(r) == 0) {
        double e[4] = {q, p, 0, 1};
        num = solve_cubic(e, s);
        s[num++] = 0;
    } else {
        double e[4] = {1.0 / 2 * r * p - 1.0 / 8 * q * q, -r, -1.0 / 2 * p, 1};
        solve_cubic(e, s);
        double z = s[0];
        double u = z * z - r;
        double v = 2 * z - p;
        if (dcmp(u) == 0) u = 0; else if (dcmp(u) > 0) u = sqrt(u); else return 0;
        if (dcmp(v) == 0) v = 0; else if (dcmp(v) > 0) v = sqrt(v); else return 0;
        e[0] = z - u;
        e[1] = dcmp(q) < 0 ? -v : v;
        e[2] = 1;
        num = solve_quadric(e, s);
        e[0] = z + u;
        e[1] = dcmp(q) < 0 ? v : -v;
        e[2] = 1;
        num += solve_quadric(e, s + num);
    }
    double sub = 1.0 / 4 * A;
    for (int i = 0; i < num; ++i) s[i] -= sub;
    return num;
}
