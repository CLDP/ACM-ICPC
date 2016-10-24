#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <unordered_map>
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
    int N, S, T, M;
    cin >> N >> S >> T >> M;
    int s = N + M + M + 1, t = s + 1;
    unordered_map<string, int> SC, TC, CC;
    for (int i = 1; i <= S; ++i) {
        string P;
        cin >> P;
        SC[P] = i;
        x[s].push_back(make_pair(i, 1));
    }
    for (int i = 1; i <= T; ++i) {
        string P;
        cin >> P;
        TC[P] = i + S;
        x[i + S].push_back(make_pair(t, 1));
    }
    int MM = S + T;

    for (int i = 1; i <= M; ++i) {
        x[N + i].push_back(make_pair(N + M + i, 1));
        int L;
        cin >> L;
        for (int j = 0; j < L; ++j) {
            string P;
            cin >> P;
            if (SC.find(P) != SC.end()) {
                int a = SC[P];
                x[a].push_back(make_pair(N + i, 1));
                continue;
            } 
            if (TC.find(P) != TC.end()) {
                int a = TC[P];
                x[N + M + i].push_back(make_pair(a, 1));
                continue;
            } 
            if (CC.find(P) == CC.end()) CC[P] = ++MM;
            int a = CC[P];
            x[a].push_back(make_pair(N + i, 1));
            x[N + M + i].push_back(make_pair(a, 1));
        }
    }
    cout << max_flow(s, t, t) << endl;
    return 0;
}
