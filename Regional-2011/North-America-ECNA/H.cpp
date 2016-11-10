#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 200;

bool z[MAXN];
long long dl[MAXN], dr[MAXN];
int l[MAXN], r[MAXN], pa[MAXN];
bool nl[MAXN], nr[MAXN];
long long pp[MAXN], qq[MAXN];
long long ans;


long long gcd(long long a, long long b) {
    while (b > 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int dfs(int aa, long long p, long long q) {
    long long ap, aq, x, y;
    x = dl[aa];
    y = dr[aa];

    long long temp = gcd(y * p, (x + y) * q);
    ap = y * p / temp;
    aq = (x + y) * q / temp;

    if (nl[aa]) {
        dfs(l[aa], ap, aq);
    } else {
        pp[l[aa]] = ap;
        qq[l[aa]] = aq;
        ans = ans / gcd(ans, aq) * aq;
    }

    temp = gcd(x * p, (x + y) * q);
    ap = x * p / temp;
    aq = (x + y) * q / temp;

    if (nr[aa]) {
        dfs(r[aa], ap, aq);
    } else {
        pp[r[aa]] = ap;
        qq[r[aa]] = aq;
        ans = ans / gcd(ans, aq) * aq;
    }
    return 0;
}


int main() {
    int n, times = 0;
    while (cin >> n) {
        if (n == 0) break;

        for (int i = 1; i <= n; ++i) {
            cin >> dl[i] >> dr[i];
            z[i] = nl[i] = nr[i] = pp[i] = qq[i] = 0;

            char p, q;
            cin >> p >> q >> l[i] >> r[i];
            if (p == 'A') {
                nl[i] = true;
                pa[l[i]] = i;
                z[l[i]] = true;
            }
            if (q == 'A') {
                nr[i] = true;
                pa[r[i]] = i;
                z[r[i]] = true;
            }
        }

        ans = 1;
        int a, c, d;
        for (a = 1; a <= n; ++a) 
         if (z[a]) continue; else break;
        dfs(a, 1, 1);

        cin >> c >> d;
        long long now;
        long long anst = ans;
        now = ans / qq[c] * pp[c];
        ans = now;
        int b = 1;
        while (ans < d) {
            ans += now;
            ++b;
        }

        ans = 0;
        for (int i = 1; i <= n + 1; ++i) ans += anst / qq[i] * pp[i];
        
        cout << "Case " << ++times << ": " << ans * b << endl;
    }
}
