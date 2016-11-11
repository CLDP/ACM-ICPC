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

const int MAXN = 1000;
const int INF = 1000000000;


int f[33];
string X[33];
vector<pair<int, int> > x[MAXN];


int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0, now, ans = 0;
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
                fi[p->first] = p - x[i].begin();
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
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
    int times;
    cin >> times;
    while (times--) {
        int N;
        cin >> N;
        memset(f, 0, sizeof(f));
        for (int i = 0; i < N; ++i) {
            cin >> X[i];
            for (int j = 0; j < N; ++j) {
                if (X[i][j] == '1') f[i] += 2;
                if (X[i][j] == 'd') f[i] += 1;
            }
        }
        
        int cnt = 0;
        for (int i = 0; i < N; ++i)
         for (int j = i + 1; j < N; ++j)
          if (X[i][j] == '.') ++cnt;
        
        for (int i = 0; i < N; ++i) {
            int temp = f[i];
            for (int j = 0; j < N; ++j)
             if (X[i][j] == '.') {
                 X[j][i] = '0';
                 temp += 2;
             }

            cnt -= (temp - f[i]) / 2;
            
            for (int j = 1; j <= N + cnt + 2; ++j) x[j].clear();
            bool flag = true;
            int cntT = 0;
            for (int j = 0; j < N; ++j) {
                if (j == i) continue;
                if (temp < f[j]) {
                    flag = false;
                    break;
                }
                x[N + cnt + 1].push_back(make_pair(j + 1, temp - f[j]));
                
                for (int k = j + 1; k < N; ++k) {
                    if (X[j][k] == '.') {
                        ++cntT;
                        x[j + 1].push_back(make_pair(N + cntT, 2));
                        x[k + 1].push_back(make_pair(N + cntT, 2));
                        x[N + cntT].push_back(make_pair(N + cnt + 2, 2));
                    }
                }
            }
            
            if (max_flow(N + cnt + 1, N + cnt + 2, N + cnt + 2) == cnt + cnt && flag) cout << i + 1 << " ";
             
            cnt += (temp - f[i]) / 2;
            for (int j = 0; j < N; ++j)
             if (X[i][j] == '.') X[j][i] = '.';
        }
        cout << endl;
        
    }
    return 0;
}
