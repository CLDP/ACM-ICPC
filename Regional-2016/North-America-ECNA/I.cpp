#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200100;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];

// n must be total number of vertices
// If too slow, try to do something obvious before call this function
int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    // vector<bool> z(n + 1, 0);
    
    int i = 0, now, ans = 0;
    hh[0] = n;
    
    i = s;
    now = INF;
    
    // while (true) 
    while (h[s] < n) {
        // z[i] = true;
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            // if (p->second > 0 && !z[p->first])
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
                    // z = vector<bool> (n + 1, false);
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        // if (!flag && i == s) break;
        
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
    int N, M, K;
    cin >> N >> M >> K;
    int s = N + M + K + 1, t = s + 1;
    for (int i = 1; i <= N; ++i) {
        x[s].push_back(make_pair(i, 1));
        int MM, a;
        cin >> MM;
        for (int j = 0; j < MM; ++j) {
            cin >> a;
            x[i].push_back(make_pair(N + a, 1));
        }
    }
    vector<bool> Z(M + 1, false);
    for (int i = 1; i <= K; ++i) {
        vector<int> S;
        int MM, a;
        cin >> MM;
        for (int j = 0; j < MM; ++j) {
            cin >> a;
            S.push_back(a);
        }
        int TT;
        cin >> TT;
        for (int j = 0; j < S.size(); ++j) {
            x[N + S[j]].push_back(make_pair(N + M + i, 1));
            Z[S[j]] = true;
        }
        x[N + M + i].push_back(make_pair(t, TT));
    }
    for (int i = 1; i <= M; ++i) {
        if (Z[i]) continue;
        x[N + i].push_back(make_pair(t, 1));
    }
    cout << max_flow(s, t, t) << endl;
    return 0;
}
