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
    long long t;
    while (b > 0) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}


int dfs(int aa, long long p, long long q) {
    long long ap, aq, agcd, a, b, c, d, x, y;
    x = dl[aa];
    y = dr[aa];
    a = y / gcd(y, q);
    b = a / gcd(a, x+y);
    c = (x+y) / gcd(x+y, a);
    d = p / gcd(p, c);
    ap = b*d;
    
    a = (x+y) / gcd(x+y, p);
    b = a / gcd(a, y);
    c = y / gcd(y, a);
    d = q / gcd(q, c);
    aq = b*d;
    
    if (nl[aa]) {
        dfs(l[aa], ap, aq);
    } else {
        pp[l[aa]] = ap;
        qq[l[aa]] = aq;
        ans = ans / gcd(ans, aq) * aq;
    }

    a = x / gcd(x, q);
    b = a / gcd(a, x+y);
    c = (x+y) / gcd(x+y, a);
    d = p / gcd(p, c);
    ap = b*d;
    
    a = (x+y) / gcd(x+y, p);
    b = a / gcd(a, x);
    c = x / gcd(x, a);
    d = q / gcd(q, c);
    aq = b*d;
    
    if (nr[aa]) {
        dfs(r[aa], ap, aq);
    } else {
        pp[r[aa]] = ap;
        qq[r[aa]] = aq;
        ans = ans / gcd(ans, aq) * aq;
    }
}


int main() {
    int n, nn = 0;
    cin >> n;
    while (n != 0) {
        ++nn;
        int a, b, c, d;
        char p, q;

        memset(z, 0, sizeof(z));
        memset(dl, 0, sizeof(dl));
        memset(dr, 0, sizeof(dr));
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(nl, 0, sizeof(nl));
        memset(nr, 0, sizeof(nr));
        memset(pp, 0, sizeof(pp));
        memset(qq, 0, sizeof(qq));
        for (int i = 1; i <= n; ++i) {
            cin >> dl[i] >> dr[i];
            cin >> p;
            ans = 1;
            while (p != 'W' && p != 'A') cin >> p;
            cin >> q;
            while (q != 'W' && q != 'A') cin >> q;
            cin >> a >> b;
            l[i] = a;
            r[i] = b;
            if (p == 'A') {
                nl[i] = true;
                pa[a] = i;
                z[a] = true;
            }
            if (q == 'A') {
                nr[i] = true;
                pa[b] = i;
                z[b] = true;
            }
        }

        for (a = 1; a <= n; ++a) 
         if (z[a]) continue; else break;
        dfs(a, 1, 1);
        cin >> c >> d;
        long long now;
        long long anst = ans;
        now = ans / qq[c] * pp[c];
        ans = now;
        b = 1;
        while (ans < d) {
            ans += now;
            ++b;
        }

        ans = 0;
        for (int i = 1; i <= n+1; ++i) {
            ans = ans + anst / qq[i] * pp[i];
        }
        
        cout << "Case " << nn << ": " << ans*b << endl;
        cin >> n;
    }
}
