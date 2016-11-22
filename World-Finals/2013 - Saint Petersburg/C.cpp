#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 25010;
const int INF = 1000000000;


int N, M, C;
int D[MAXN];
vector<pair<int, int> > y[MAXN];

int n;
vector<pair<int, int> > x[MAXN];
vector<pair<int, int> >::iterator fan[MAXN];


int SPFA() {
    vector<bool> z(N + 1, false);
    for (int i = 1; i <= N; ++i) D[i] = INF;
    
    D[1] = 0;
    z[1] = true;
    queue<int> que;
    que.push(1);
    
    while (!que.empty()) {
        int s = que.front();
        que.pop();
        for (int i = 0; i < y[s].size(); ++i)
         if (D[y[s][i].first] > D[s] + y[s][i].second) {
             D[y[s][i].first] = D[s] + y[s][i].second;
             if (!z[y[s][i].first]) {
                 z[y[s][i].first] = true;
                 que.push(y[s][i].first);
             }
         }
        
        z[s] = false;
    }
    
    for (int i = 1; i <= N; ++i) {
        vector<pair<int, int> > newX;
        for (int j = 0; j < y[i].size(); ++j) 
         if (D[i] == D[y[i][j].first] + y[i][j].second) 
          newX.push_back(make_pair(y[i][j].first, 1));
        y[i] = newX;
    }
    
    return 0;
}


int max_flow(int s, int t) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    
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
    cin >> N >> M >> C;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        y[a].push_back(make_pair(b, c));
        y[b].push_back(make_pair(a, c));
    }
    SPFA();
    vector<pair<int, int> > S;
    for (int i = 0; i < C; ++i) {
        int a;
        cin >> a;
        S.push_back(make_pair(D[a], a));
    }
    sort(S.begin(), S.end());
    
    n = N + 1;
    int ans = 0;
    for (int i = 0; i < S.size(); ) {
        for (int j = 1; j <= n; ++j) x[j].clear();
        int temp = S[i].first;
        map<int, int> A;
        while (i < S.size() && S[i].first == temp) {
            ++A[S[i].second];
            ++i;
        }
        queue<int> que;
        vector<bool> z(n + 1, false);
        map<int, int>::iterator iter = A.begin();
        int total = 0;
        while (iter != A.end()) {
            if (iter->first == 1) {
                ans += iter->second;
                ++iter;
            } else {
                x[n].push_back(make_pair(iter->first, min(iter->second, (int)y[iter->first].size())));
                total += min(iter->second, (int)y[iter->first].size());
                que.push(iter->first);
                z[iter->first] = true;
                ++iter;
            }
        }
        if (total == 1) {
            ans += 1;
            continue;
        }
        
        int a = 0, b = 0;
        while (!que.empty()) {
            int j = que.front();
            que.pop();
            ++a;
            x[j] = y[j];
            b += x[j].size();
            for (int k = 0; k < x[j].size(); ++k)
             if (!z[x[j][k].first]) {
                 que.push(x[j][k].first);
                 z[x[j][k].first] = true;
             }
        }
            
        ans += max_flow(n, 1);
    }
    
    cout << ans << endl;
    
    return 0;
}
