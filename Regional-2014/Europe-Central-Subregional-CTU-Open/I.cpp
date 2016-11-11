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

int n;
vector<int> e[10005];
int f[10005];
int sz[10005];
int res[10005];
int rev[10005];

void getSize(int ind) {
    sz[ind] = 1;
    for (int i = 0; i < e[ind].size(); ++i) {
        if (e[ind][i] != f[ind]) {
            getSize(e[ind][i]);
            sz[ind] += sz[e[ind][i]];
        }
    }
}

int getRoot(int ind) {
    for (int i = 0; i < e[ind].size(); ++i) {
        if (sz[e[ind][i]] > sz[ind] / 2) {
            sz[ind] -= sz[e[ind][i]];
            sz[e[ind][i]] += sz[ind];
            f[ind] = e[ind][i];
            f[e[ind][i]] = -1;
            return getRoot(e[ind][i]);
        }
    }
    return ind;
}

void assign(int ind, vector<int> &v) {
    res[ind] = v.back();
    v.pop_back();
    for (int i = 0; i < e[ind].size(); ++i)
        if (e[ind][i] != f[ind]) assign(e[ind][i], v);
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; ++i) e[i].clear();
        f[0] = -1;
        for (int i = 1; i < n; ++i) {
            cin >> f[i];
            e[i].push_back(f[i]);
            e[f[i]].push_back(i);
        }
        
        getSize(0);

        int r = getRoot(0);
        
        int st = 0;
        for (int i = 0; i < e[r].size(); ++i)
            if (sz[e[r][i]] == sz[r] / 2) st = i;
        res[r] = 0;
        int cnt = 1;
        int st_cp = st;

        do {
            vector<int> v;
            for (int i = 0; i < sz[e[r][st]]; ++i) {
                v.push_back(cnt);
                cnt += 2;
                if (cnt >= n) cnt = 2;
            }
            assign(e[r][st], v);
            st = (st + 1) % e[r].size();
        }
        while (st_cp != st);
        
        for (int i = 0; i < n; ++i) rev[res[i]] = i;
        cout << rev[0];
        for (int i = 1; i < n; ++i) cout << " " << rev[i];
        cout << endl;
    }
    
    return 0;
}
