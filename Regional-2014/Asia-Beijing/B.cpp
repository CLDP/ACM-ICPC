#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int rr[10][10];
int c[30];

int main() {
    int t;
    
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        vector<pair<int, int> > kk;
        for (int i = 0; i <= n + 1; ++i)
            for (int j = 0; j <= m + 1; ++j) rr[i][j] = 0;
        for (int i = 1; i <= k; ++i) {
            scanf("%d", &c[i]);
            kk.push_back(make_pair(c[i], i));
        }
        sort(kk.rbegin(), kk.rend());
        vector<pair<int, int> > p(n * m);
        int l = 0, r = n * m - 1;
        if (n == 2) {
            for (int i = 0; i < m; ++i)
                p[i] = make_pair(i % 2, i);
            for (int i = m - 1; i >= 0; --i)
                p[i + m] = make_pair((i + 1) % 2, i);
        } else 
        if (m == 2) {
            for (int i = 0; i < n; ++i)
                p[i] = make_pair(i, i % 2);
            for (int i = n - 1; i >= 0; --i)
                p[i + n] = make_pair(i, (i + 1) % 2);
        } else {
            for (int s = 0; s < m + n; s += 2)
                for (int i = s; i >= 0; --i)
                    if ((i < n) && (s - i < m))
                        p[l++] = make_pair(i, s - i);
            for (int s = m + n - 2 - ((m + n + 1) % 2); s >= 0; s -= 2)
                for (int i = 0; i <= s; ++i)
                    if ((i < n) && (s - i < m))
                        p[r--] = make_pair(i, s - i);
        }

        l = 0, r = n * m - 1;
        for (int i = 0; i < kk.size(); ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < kk[i].first; ++j) {
                    rr[p[l].first][p[l].second] = kk[i].second;
                    ++l;
                }
            } else {
                for (int j = 0; j < kk[i].first; ++j) {
                    rr[p[r].first][p[r].second] = kk[i].second;
                    --r;
                }
            }
        }
        
        printf("Case #%d:\n", tt);
        bool check = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (rr[i][j] == rr[i+1][j]) check = false;
                if (rr[i][j] == rr[i][j+1]) check = false;
            }
        if (check) {
            printf("YES\n");
            for (int i = 0; i < n; ++i) {
                printf("%d", rr[i][0]);
                for (int j = 1; j < m; ++j) printf(" %d", rr[i][j]);
                printf("\n");
            }
        } else
            printf("NO\n");
    }

    return 0;
}
