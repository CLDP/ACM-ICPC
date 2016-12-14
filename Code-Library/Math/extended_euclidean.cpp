// The result guarantees that |x|+|y| is minimized
int extended_euclidean(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int res = extended_euclidean(b, a % b, y, x);
    y -= a / b * x;
    return res;
}

int modular(int x, int m) {
    if (x < 0) x += abs(x / m) * m + m;
    return x % m;
}

// a and m must be relatively prime
// return x such that ax = 1 mod m
// otherwise return ax = gcd(a, m) mod m
int modular_inverse(int a, int m) {
    int x, y;
    extended_euclidean(a, m, x, y);
    return modular(x, m);
}
