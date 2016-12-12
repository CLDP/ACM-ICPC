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

int mexp[MAXN], id[MAXN];

bool logcmp(const int &a, const int &b) {
    return mexp[a] < mexp[b];
}

// Find x such that a^x = b mod n, n is prime
// This algorithm is an O(sqrt n) brute force
// Be careful about integer overflow
int modular_log(int a, int b, int n) {
    int m = (int)ceil(sqrt(n));
    int inv = modular_inverse(modular_power(a, m, n), n);
    id[0] = 0;
    mexp[0] = 1;
    for (int i = 1; i < m; ++i) {
        id[i] = i;
        mexp[i] = (1LL * mexp[i - 1] * a) % n;
    }
    stable_sort(id, id + m, logcmp);
    sort(mexp, mexp + m);
    for (int i = 0; i < m; ++i) {
        int j = lower_bound(mexp, mexp + m, b) - mexp;
        if (j < m && mexp[j] == b) return i * m + id[j];
        b = (1LL * b * inv) % n;
    }
    return -1;
}
