const double PI = acos(-1.0);
const double EPS = 1e-8;
const double genx = (rand() % 1000) / 100.0;
const int MAXN = 10;

int dcmp(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

double f(double a[], int n, double x) {
    double ans = 0, xx = 1;
    for (int i = 0; i <= n; ++i) {
        ans += a[i] * xx;
        xx *= x;
    }
    return ans;
}

double newton(double a[], double b[], int n) {
    double x = genx, y, lastx = x - 1;
    while (y = f(a, n, x), dcmp(lastx - x)) {
        lastx = x;
        double dy = f(b, n - 1, x);
        if (!dcmp(dy)) x = genx; else x = x - y / dy;
    }
    return x;
}

// Find roots for f(x)=sum a_ix^i = 0 using Newton's method
// The performance is extremely well when all roots are far away
// Otherwise it may go into infinite loop
void solve(double a[], double x[], int n) {
    double b[MAXN];
    for (int j = n; j > 0; --j) {
        for (int i = 0; i < j; ++i) b[i] = a[i + 1] * (i + 1);
        x[j - 1] = newton(a, b, j);
        b[j] = 0;
        for (int i = j - 1; i >= 0; --i) b[i] = a[i + 1] + b[i + 1] * x[j - 1];
        for (int i = 0; i < j; ++i) a[i] = b[i];
    }
}
