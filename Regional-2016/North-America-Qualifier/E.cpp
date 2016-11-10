#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


const int MAXN = 200100;
const int INF = 1000000000;

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
    int N;
    cin >> N;
    string P[200];
    getline(cin, P[0]);
    for (int i = 0; i < N; ++i) {
        getline(cin, P[i + i]);
        if (i != N - 1) getline(cin, P[i + i + 1]);
    }
    
    int NN = (N - 1) * (N - 1), s = NN + 1, t = s + 1, ans = 0;
    
    for (int i = 1; i < N + N - 1; i += 2)
     for (int j = 1; j < N + N - 1; j += 2) {
         int a = i / 2 * (N - 1) + j / 2 + 1, cnt = 0;
         if (P[i - 1][j] == '.') ++cnt;
         if (P[i + 1][j] == '.') ++cnt;
         if (P[i][j - 1] == '.') ++cnt;
         if (P[i][j + 1] == '.') ++cnt;
         if (cnt < 2) continue;
         bool flag = i / 2 % 2 == j / 2 % 2;
         
         if (P[i - 1][j] == '.') {
             if (i == 1) {
                 --cnt;
                 if (cnt > 0) ++ans;
             } else
             if (flag) {
                 int b = (i - 2) / 2 * (N - 1) + j / 2 + 1;
                 x[a].push_back(make_pair(b, 1));
             }
         }
         if (P[i + 1][j] == '.') {
             if (i == N + N - 3) {
                 --cnt;
                 if (cnt > 0) ++ans;
             } else 
             if (flag) {
                 int b = (i + 2) / 2 * (N - 1) + j / 2 + 1;
                 x[a].push_back(make_pair(b, 1));
             }
         }
         if (P[i][j - 1] == '.') {
             if (j == 1) {
                 --cnt;
                 if (cnt > 0) ++ans;
             } else
             if (flag) {
                 int b = i / 2 * (N - 1) + (j - 2) / 2 + 1;
                 x[a].push_back(make_pair(b, 1));
             }
         } 
         if (P[i][j + 1] == '.') {
             if (j == N + N - 3) {
                 --cnt;
                 if (cnt > 0) ++ans;
             } else 
             if (flag) {
                 int b = i / 2 * (N - 1) + (j + 2) / 2 + 1;
                 x[a].push_back(make_pair(b, 1));
             }
         }
         
         if (cnt < 2) continue;
         --cnt;
         if (flag) x[s].push_back(make_pair(a, cnt)); else x[a].push_back(make_pair(t, cnt));
     }
    
    cout << max_flow(s, t, t) + ans + 1 << endl;
    
    return 0;
}
