#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct castle {
    int a, m, g;
};

struct node {
    int need, left;
};

bool compare(node n1, node n2) {
    if (n1.left == n2.left) return n1.need > n2.need;
    return n1.left > n2.left;
}

vector<castle> c;
vector<int> e[105];

node solve(int ind, int f) {
    node res;
    vector<node> nn;
    res.need = c[ind].a;
    res.left = c[ind].a - c[ind].m - c[ind].g;
    for (int i = 0; i < e[ind].size(); ++i) {
        if (e[ind][i] != f) nn.push_back(solve(e[ind][i], ind));
    }
    
    sort(nn.begin(), nn.end(), compare);
    
    for (int i = 0; i < nn.size(); ++i) {
        if (nn[i].need > res.left) {
            res.need += nn[i].need - res.left;
            res.left = nn[i].need;
        }
        res.left = res.left - (nn[i].need - nn[i].left);
    }
    return res;
}

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        castle tc;
        c.clear();
        
        for (int i = 0; i < N; ++i) {
            cin >> tc.a >> tc.m >> tc.g;
            if (tc.m + tc.g > tc.a) tc.a = tc.m + tc.g;
            e[i].clear();
            c.push_back(tc);
        }
        
        for (int i = 1; i < N; ++i) {
            int j, k;
            cin >> j >> k;
            --j;
            --k;
            e[j].push_back(k);
            e[k].push_back(j);
        }
        
        int best = 20000000;
        for (int i = 0; i < N; ++i) {
            node temp = solve(i, -1);
            if (temp.need < best) best = temp.need;
        }
        
        cout << "Case " << ++times << ": " << best << endl;
    }
    
    return 0;
}
