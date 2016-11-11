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

struct node {
    long long t;
    int d, remD;
    int cn, cid;
};

map<int, node> m;
vector<pair<int, node> > cur;
node tn;
int n, s, dt, d0 = -1;
int lc[200005];

void conV(node &n1, int curD) {
    if (curD > n1.remD + n1.d) {
        n1.t = 0;
        n1.d = curD;
        n1.remD = 0;
    } else {
        n1.t = n1.t >> (curD - n1.d);
        n1.remD = n1.remD - curD + n1.d;
        n1.d = curD;
    }
}

long long getEffect(node &n1, int curD) {
    if (curD > n1.remD + n1.d) return 0;
    return n1.t >> (curD - n1.d);
}

long long pf[60];

int main() {
    pf[0] = 1;
    for (int i = 1; i < 57; ++i) pf[i] = pf[i-1] * 2;

    cin >> n >> s >> dt;
    tn.t = 0;
    tn.d = -1;
    tn.remD = 0;
    tn.cn = 0;
    tn.cid = -1;
    m[s] = tn;
    int minD = 1;
    long long tmp = 2;
    while (tmp <= dt) {
        minD++;
        tmp *= 2;
    }
    
    for (int i = 0; i < n; ++i) {
        int d, l, h;
        cin >> d >> l >> h;
        if (d != d0) {
            for (int j = 0; j < cur.size(); ++j) {
                map<int, node>::iterator it = m.lower_bound(cur[j].first);
                if (it != m.end()) {
                    if (cur[j].second.t >= getEffect(it->second, d0)) continue;
                }
                while (true) {
                    it = m.upper_bound(cur[j].first);
                    if (it == m.begin()) {
                        m[cur[j].first] = cur[j].second;
                        break;
                    }
                    --it;
                    if (cur[j].second.t <= getEffect(it->second, d0))
                        m.erase(it);
                    else {
                        m[cur[j].first] = cur[j].second;
                        break;
                    }
                }
            }
            cur.clear();
            d0 = d;
        }
        map<int, node>::iterator it = m.lower_bound(l);
        if (it != m.end()) {
            tn = it->second;
            lc[i] = tn.cid;
            if (tn.d != d - 1) conV(tn, d-1);
            int nl = h - tn.t;
            if (tn.d == d - 1) {
                tn.t += dt;
                tn.remD = max(tn.remD, minD);
                tn.d = d;
            } else {
                conV(tn, d);
                tn.t += dt;
                tn.remD = max(tn.remD, minD);
            }
            tn.cn++;
            tn.cid = i;
            while (pf[tn.remD] <= tn.t) tn.remD++;
            cur.push_back(make_pair(nl, tn));
        }
    }
    for (int j = 0; j < cur.size(); ++j) {
        map<int, node>::iterator it = m.lower_bound(cur[j].first);
        if (it != m.end()) {
            if (cur[j].second.t >= getEffect(it->second, d0)) continue;
        }
        while (true) {
            it = m.upper_bound(cur[j].first);
            if (it == m.begin()) {
                m[cur[j].first] = cur[j].second;
                break;
            }
            --it;
            if (cur[j].second.t <= getEffect(it->second, d0))
                m.erase(it);
            else {
                m[cur[j].first] = cur[j].second;
                break;
            }
        }
    }
    
    cout << m.rbegin()->first << " " << m.rbegin()->second.cn << endl;
    vector<int> cs;
    int ind = m.rbegin()->second.cid;
    while (ind != -1) {
        cs.push_back(ind);
        ind = lc[ind];
    }
    if (cs.size() > 0) {
        for (int i = cs.size() - 1; i > 0; --i) cout << cs[i] + 1 << " ";
        cout << cs[0] + 1;
    }
    cout << endl;

    return 0;
}
