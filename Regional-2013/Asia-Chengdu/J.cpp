#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

long long p, m;

long long gcd(long long a, long long b) {
    while (b > 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long solve(long long x, long long y) {
    if ((x == -1) || (y == -1)) return 0;
    if (x == 0) {
        if (y < m) return 0;
        return ((y - m) / p + 1);
    }
    if (y == 0) {
        if (x < m) return 0;
        return ((x - m) / p + 1);
    }
    
    long long x1 = x / p, x2 = y / p, y1 = x % p, y2 = y % p;
    long long res = x1 * x2 * p + y1 * x2 + y2 * x1 + x1 + x2;
    if (y1 + y2 >= p + m) {
        res += y1 + y2 - p + 2;        
    } else {
        if (y1 + y2 >= m) {
            if ((y1 >= m) && (y2 >= m))
                res += m + 1;
            else 
            if (y1 >= m)
                res += y2 + 1;
            else 
            if (y2 >= m)
                res += y1 + 1;
            else
                res += (y1 + y2 - m + 1);
        }
    }
    return res;
}


int main() {
    int n;
    long long a, b, c, d;   
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b >> c >> d >> p >> m;
        long long num = 0, den = (b - a + 1) * (d - c + 1);
        num = solve(b, d) - solve(a - 1, d) - solve(b, c - 1) + solve(a - 1, c - 1);
        long long cd = gcd(num, den);
        num = num / cd;
        den = den / cd;
        cout << "Case #" << i << ": " << num << "/" << den << endl;
    }
    
    return 0;
}
