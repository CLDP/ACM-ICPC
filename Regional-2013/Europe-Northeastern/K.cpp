#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

const int MAXN = 100005;

int b[MAXN], l[MAXN], c[MAXN], oc[MAXN];
set<int> s;

int main() {
    freopen("kabaleo.in", "r", stdin);
    freopen("kabaleo.out", "w", stdout);
    int n, p, color, h;
    
    cin >> n >> p >> color >> h;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        ++c[b[i]];
        ++oc[b[i]];
    }
    for (int i = 1; i <= p; ++i) cin >> l[i];

    if (n == 1) {
        if (l[p] == h)
            cout << 1 << endl << 1 << endl;
        else
            cout << 0 << endl << endl;
        return 0;
    }
    
    for (int i = 2; i <= p; ++i) {
        if (l[i] != h) {
            --c[h];
            ++c[l[i]];
        }
    }
    
    ++c[l[1]];
    int m1 = 0, m1i, m2 = 0, m2i;
    for (int i = 1; i <= color; ++i)
     if (i != h) {
         if (c[i] > m1) {
             m2 = m1;
             m2i = m1i;
             m1 = c[i];
             m1i = i;
         } else 
         if (c[i] > m2) {
             m2 = c[i];
             m2i = i;
         }
     }
    
    int res = 0;
    for (int i = 1; i <= color; ++i) {
        if (i == m1i) --m1;
        if (i == m2i) --m2;
        if (i == h) --c[h];
        if ((c[h] > m1) && (c[h] > m2)) {
            res += oc[i];
            s.insert(i);
        }
        if (i == h) ++c[h];
        if (i == m1i) ++m1;
        if (i == m2i) ++m2;
    }
    
    cout << res << endl;
    for (int i = 1; i <= n; ++i)
     if (s.find(b[i]) != s.end()) {
         if (res > 0)
             cout << i << " ";
         else
             cout << i;
         --res;
     } 
    cout << endl;
    
    return 0;
}
