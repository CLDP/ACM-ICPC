#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int n;

struct seg {
    int a, b, id, d;
};

vector<seg> sto, eno;
        
unordered_map<int, int> st_idx;
unordered_map<int, int> en_idx;

bool storder(seg s1, seg s2) {
    return s1.a < s2.a;
}

bool enorder(seg s1, seg s2) {
    return s1.b < s2.b;
}

int f[303][303];

int solve(int i1, int i2, int l, int r) {
    if (f[i1][i2] != -1) return f[i1][i2];  
    vector<int> s, e, d;
    int dm = -1, da, db;
    for (int i = 0; i < n; ++i) {
        if ((sto[i].a >= l) && (sto[i].b <= r)) {
            s.push_back(sto[i].a);
            d.push_back(sto[i].d);
            if (sto[i].d > dm) {
                dm = sto[i].d;
                da = sto[i].a;
                db = sto[i].b;
            }
        }
        if ((eno[i].a >= l) && (eno[i].b <= r)) {
            e.push_back(eno[i].b);
            if (eno[i].d > dm) {
                dm = eno[i].d;
                da = eno[i].a;
                db = eno[i].b;
            }
        }
    }
    
    if (s.empty()) {
        f[i1][i2] = 0;
        return 0;
    } else 
    if (s.size() == 1) {
        f[i1][i2] = d[0];
        return d[0];
    }
    
    int ind = 0, best = -1, ind2 = 0;
    for (int i = 0; i < e.size(); ++i) {
        if ((da <= e[i]) && (e[i] <= db)) {
            while ((ind < s.size()) && (s[ind] <= e[i])) ++ind;
            while ((ind2 + 1 < e.size()) && (e[ind2 + 1] < e[i])) ++ind2;
            int cur = dm;
            if ((ind2 < e.size()) && (e[ind2] < e[i]))
                cur += solve(i1, en_idx[e[ind2]], l, e[ind2]);
            if (ind < s.size())
                cur += solve(st_idx[s[ind]], i2, s[ind], r);
            if ((cur < best) || (best == -1))
                best = cur;
        }
    }
    
    f[i1][i2] = best;
    return best;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        seg ts;
        sto.clear();
        eno.clear();
        for (ts.id = 0; ts.id < n; ++ts.id) {
            cin >> ts.a >> ts.b >> ts.d;
            sto.push_back(ts);
            eno.push_back(ts);
        }
        
        sort(sto.begin(), sto.end(), storder);
        sort(eno.begin(), eno.end(), enorder);
        
        st_idx.clear();
        en_idx.clear();
        
        int cnt = 0;
        st_idx[sto[0].a] = cnt++;
        for (int i = 1; i < n; ++i)
            if (sto[i].a != sto[i-1].a) st_idx[sto[i].a] = cnt++;
        cnt = 0;
        en_idx[eno[0].b] = cnt++;
        for (int i = 1; i < n; ++i)
            if (eno[i].b != eno[i-1].b) en_idx[eno[i].b] = cnt++;
                
        for (int i = 0; i < sto.size(); ++i)
            for (int j = 0; j < eno.size(); ++j) f[i][j] = -1;
        cout << solve(0, eno.size() - 1, sto[0].a, eno[n-1].b) << endl;
    }

    return 0;
}
