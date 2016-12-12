// all solutions for ax = b mod n, n > 0
int modular_linear_equation_solver(int a, int b, int n) {
    int x, y;
    int d = extended_euclidean(a, n, x, y);
    if (b % d != 0) return -1;
    int e = x * (b / d) % n;
    for (int i = 0; i < d; ++i) cout << modular(e + i * (n / d), n) << endl;
    return 0;
}

// Given bi, wi, with gcd(wi, wj) = 1
// Find an x such that x = bi mod wi
// Be careful about integer overflow
int chinese_remainder(int b[], int w[], int len) {
    int W = 1, ans = 0;
    for (int i = 0; i < len; ++i) W *= w[i];
    for (int i = 0; i < len; ++i) {
        int Wi = W / w[i];
        int y = modular_inverse(Wi, w[i]);
        ans = modular(ans + y * Wi * b[i], W);
    }
    return ans;
}
