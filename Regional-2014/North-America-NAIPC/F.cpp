#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const double INF = 1e20;

int N, M, W, H;
double L[MAXN];
double C[MAXN];
double CC[MAXN][MAXN];
double HH[MAXN];


vector<pair<int, double> > x[MAXN + MAXN + 2];


double max_flow(int s, int t, int n) {
    vector<double> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0;
    double now, ans = 0;
    hh[0] = n;
    
    i = s;
    now = INF;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<pair<int, double> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 1e-7 && h[p->first] + 1 == h[i]) {
                flag = true;
                if (p->second < now) now = p->second;
                fa[p->first] = i;
                fi[p->first] = p - x[i].begin();
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
                        p->second -= now;
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
            if (p->second > 1e-7 && h[p->first] < min) min = h[p->first];
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
    cin >> N >> M >> W >> H;
    for (int i = 1; i <= M; ++i) cin >> C[i];
    for (int i = 1; i <  N; ++i) cin >> L[i];
    L[N] = W;
    for (int i = N; i >= 2; --i) L[i] = L[i] - L[i - 1];
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) cin >> CC[i][j];
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         double CCC;
         cin >> CCC;
         HH[i] += CC[i][j] / L[i];
         C[j] -= CC[i][j];
         CC[i][j] = CCC - CC[i][j];
     }
    
    double l = 0, r = 0, RR = 0;
    for (int i = 1; i <= N; ++i) RR = max(RR, HH[i]);
    r = RR;
    
    int s = N + M + 1, t = s + 1;
    
    while (l + 1e-5 < r) {
        double mid = (l + r) / 2;
        for (int i = 1; i <= N + M + 2; ++i) x[i].clear();
        for (int i = 1; i <= M; ++i) {
            x[s].push_back(make_pair(i, C[i]));
        }
        double TT = 0;
        for (int i = 1; i <= N; ++i) 
         if (RR - HH[i] - mid > 0) {
             x[M + i].push_back(make_pair(t, (RR - HH[i] - mid) * L[i]));
             TT += (RR - HH[i] - mid) * L[i];
         }
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) {
             x[j].push_back(make_pair(M + i, CC[i][j]));
         }
        
        double flow = max_flow(s, t, t);
        if (fabs(flow - TT) < 1e-6) r = mid; else l = mid;
    }
    
    printf("%.3lf\n", r);
    
    return 0;
}
