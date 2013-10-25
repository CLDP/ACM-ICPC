#include <iostream>
using namespace std;

const int MAXN = 501;

int n, m;
long long x[MAXN][MAXN];

int Gcd(int a, int b) {
    int t;
    while (b > 0) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int check(int a, int b) {
    for (int i = 0; i < n / a; ++i)
     for (int j = 0; j < m / b; ++j) {
         if (i == 0 && j == 0) continue;
         
         for (int p = 0; p < a; ++p)
          for (int q = 0; q < b; ++q) {
              if (x[0][0] * x[i * a + p][j * b + q] != x[i * a][j * b] * x[p][q]) return 0;
          }
     }
     
    int ans = x[0][0];
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) ans = Gcd(ans, x[i][j]);
    
    return ans;
}

int cal(int a) {
    int ans = 1,  t = 2;
    while (a > 1) {
        if (a % t != 0) {
            ++t;
            continue;
        }
        int num = 1;
        while (a % t == 0) {
            a /= t;
            ++num;
        }
        ans *= num;
    }
    
    return ans;
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; ++i) 
         for (int j = 0; j < m; ++j) cin >> x[i][j];
        
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (n % i != 0) continue;
                if (m % j != 0) continue;
                if (i == 1 && j == 1) continue;
                if (i == n && j == m) continue;
                int gcd = check(i, j);
                if (gcd > 0) ans += cal(gcd);
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
