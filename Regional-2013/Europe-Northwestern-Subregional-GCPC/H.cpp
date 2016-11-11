#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 200000;
const int INF = 100000000;


int n;
int X[301][301];
vector<pair<int, int> > x[MAXN];
vector<pair<int, int> >::iterator fan[MAXN];
int fa[MAXN], ff[MAXN], h[MAXN], hh[MAXN];


int max_flow(int s, int t) {
    int i = 0, now, ans = 0;
    
    memset(ff, 0, sizeof(ff));
    memset(fa, 0, sizeof(fa));
    memset(h,  0, sizeof(h));
    memset(hh, 0, sizeof(hh));
    hh[0] = n;
    
    i = s;
    now = INF;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] + 1 == h[i]) {
                flag = true;
                if (p->second < now) now = p->second;
                fa[p->first] = i;
                fan[p->first] = p;
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        p = fan[i];
                        i = fa[i];
                        p->second -=now;
                        x[tmp].push_back(make_pair(i, now));
                    }
                    now = INF;
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        
        int min = n-1;
        p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] < min) min = h[p->first];
            ++p;
        }
        
        --hh[h[i]];
        if (hh[h[i]] == 0) break;
        h[i] = min + 1;
        ++hh[h[i]];
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}


int main() {
    int m, a, b, c, s, t;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) {
         cin >> X[i][j];
     }
    
    cin >> s >> t;
    s = s * m + t + 1;
    t = n * m * 2 + 1;
    int two = n * m;
    
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) {
         a = i * m + j + 1;
         x[a].push_back(make_pair(a + two, X[i][j]));
         x[a + two].push_back(make_pair(a, X[i][j]));
         a += two;
         if (i == 0) {
             x[a].push_back(make_pair(t, X[i][j]));
         } else {
             b = (i-1) * m + j + 1;
             x[a].push_back(make_pair(b, min(X[i][j], X[i - 1][j])));
         }
         if (i == n-1) {
             x[a].push_back(make_pair(t, X[i][j]));
         } else {
             b = (i+1) * m + j + 1;
             x[a].push_back(make_pair(b, min(X[i][j], X[i + 1][j])));
         }
         
         if (j == 0) {
             x[a].push_back(make_pair(t, X[i][j]));
         } else {
             b = i * m + j;
             x[a].push_back(make_pair(b, min(X[i][j], X[i][j - 1])));
         }
         if (j == m-1) {
             x[a].push_back(make_pair(t, X[i][j]));
         } else {
             b = i * m + j + 2;
             x[a].push_back(make_pair(b, min(X[i][j], X[i][j + 1])));
         }
     }
    
    n = t;
    
    cout << max_flow(s, t) << endl;
    
    return 0;
}


