// return x = a^b mod n, (a, b >= 0)
int modular_power(int a, int b, int n) {
    long long d = 1, i = 0;
    while (b >= (1LL << i)) ++i;
    --i;
    while (i >= 0) {
        d = d * d % n;
        if (b & (1 << i)) d = d * a % n;
        --i;
    }
    return d;
}

// return x such that x * x = a mod n
// n is a prime and gcd(a, n) = 1
int modular_sqrt(int a, int n) {
    if (n == 2) return a % n;
    if (modular_power(a, (n - 1) / 2, n) == 1) {
        int x = 0;
        if (n % 4 == 3) {
            x = modular_power(a, (n + 1) / 4, n);
        } else {
            int b = 1;
            while (modular_power(b, (n - 1) / 2, n) == 1) ++b;
            int i = (n - 1) / 2;
            int k = 0;
            do {
                i /= 2;
                k /= 2;
                if ((1LL * modular_power(a, i, n) * modular_power(b, k, n) + 1) % n == 0) 
                    k += (n - 1) / 2;
            } while (i % 2 == 0);
            x = (1LL * modular_power(a, (i + 1) / 2, n) * modular_power(b, k / 2, n)) % n;
        }
        if (x * 2 > n) x = n - x;
        return x;
    }
    return -1;
}
