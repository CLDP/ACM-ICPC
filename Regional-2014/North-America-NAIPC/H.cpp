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
    long long profit;
    int inV;
    int outV;
};

bool compare(node n1, node n2) {
    return n1.profit < n2.profit;
}

vector<node> ns;
node tn;
vector<int> f, p, m, s;
int n;
bool outD[100005];
vector<int> e[100005];
vector<int> pos;
long long res;
bool v[100005];
bool c[100005];

int main() {
    scanf("%d", &n);
    
    f.resize(n + 1);
    p.resize(n + 1);
    m.resize(n + 1);
    s.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d %d %d %d", &f[i], &p[i], &m[i], &s[i]);
    for (int i = 1; i <= n; ++i) {
        tn.profit = m[f[i]] - p[i];
        if (tn.profit > 0) {
            e[f[i]].push_back(i);
            if (i == f[i])
                pos.push_back(i);
            else
                outD[i] = true;
        } else
            pos.push_back(i);
    }
    
    for (int i = 1; i <= n; ++i) {
        if (v[i]) continue;
        v[i] = true;
        int cur = i;
        while (!v[f[cur]] && (m[f[cur]] - p[cur] > 0)) {
            cur = f[cur];
            v[cur] = true;
        }
        if (v[f[cur]] && !c[f[cur]] && (m[f[cur]] - p[cur] > 0))
        {
            int term = cur;
            do {
                tn.outV = cur;
                tn.inV = f[cur];
                int outMax = 0, curI = f[cur];
                for (int j = 0; j < e[curI].size(); ++j) {
                    int k = e[curI][j];
                    if (k != cur) outMax = max(outMax, m[f[k]] - p[k]);
                }
                tn.profit = m[f[cur]] - p[cur] - outMax;
                ns.push_back(tn);
                cur = f[cur];
            } while (cur != term);
        }
        cur = i;
        c[cur] = true;
        while (!c[f[cur]] && (m[f[cur]] - p[cur] > 0)) {
            cur = f[cur];
            c[cur] = true;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        long long bestP = -1;
        for (int j = 0; j < e[i].size(); ++j) {
            int k = e[i][j];
            bestP = max(bestP, (long long)m[f[k]] - p[k]);
        }
        if (bestP > 0) res += bestP * (s[i] - 1);
    }
    
    sort(ns.begin(), ns.end(), compare);
    
    int ind = 0;
    while (ind <= ns.size()) {
        while (pos.size() > 0) {
            int i = pos.back();
            pos.pop_back();
            long long bestP = -1;
            for (int j = 0; j < e[i].size(); ++j) {
                int k = e[i][j];
                if ((outD[k]) || (k == i)) {
                    bestP = max(bestP, (long long)m[f[k]] - p[k]);
                    if (k != i) {
                        pos.push_back(k);
                        outD[k] = false;
                    }
                }
            }
            if (bestP > 0) res += bestP;
        }
        if (ind == ns.size()) break;
        if (outD[ns[ind].outV]) {
            outD[ns[ind].outV] = false;
            pos.push_back(ns[ind].outV);
        }
        ++ind;
    }
    
    cout << res << endl;

    return 0;
}
