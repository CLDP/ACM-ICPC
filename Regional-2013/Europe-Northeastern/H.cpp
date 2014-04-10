#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

int f[100005][34];
map<int, vector<int> > x;
int a[100005];

struct node {
    int ind, pos;
};

bool myCompare(node n1, node n2) {
    if (n1.pos == n2. pos) return n1.ind < n2.ind;
    return n1.pos < n2.pos;
}

int main() {
    freopen("hack.in", "r", stdin);
    freopen("hack.out", "w", stdout);
    int n; 
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    
    int xo = 0;
    for (int i = 0; i < n; ++i) {
        xo ^= a[i];
        if (x.find(xo) == x.end()) x[xo] = vector<int>();
        x[xo].push_back(i);
    }
    
    for (int i = 0; i < 33; ++i) f[n][i] = n;
    for (int i = n - 1; i >= 0; --i) {
        int j = a[i];
        for (int k = 0; k < 33; ++k) {
            if (j % 2 == 0)
                f[i][k] = i;
            else
                f[i][k] = f[i + 1][k];
            j = j / 2;
        }
    }
    
    long long res = 0;
    xo = 0;
    for (int i = 0; i < n; ++i) {
        vector<node> nn;
        node tmpn;
        tmpn.pos = i;
        tmpn.ind = 0;
        nn.push_back(tmpn);
        for (int k = 0; k < 33; ++k)
         if (f[i][k] != i) {
             tmpn.pos = f[i][k];
             tmpn.ind = k;
             nn.push_back(tmpn);
         }
        tmpn.pos = n + 2;
        nn.push_back(tmpn);
        sort(nn.begin(), nn.end(), myCompare);
        int j = 0, xt = a[i], l = i;
        while (j + 1 < nn.size()) {
            if (nn[j].pos != nn[j + 1].pos) {
                int xf = xt ^ xo;
                map<int, vector<int> >::iterator it = x.find(xf);
                if (it != x.end()) {
                    vector<int>::iterator low, up;
                    low = lower_bound(it->second.begin(), it->second.end(), l);
                    up = lower_bound(it->second.begin(), it->second.end(), nn[j + 1].pos);
                    res += (up - low);
                }
                l = nn[j + 1].pos;
            }
            xt = xt - (1 << nn[j + 1].ind);
            ++j;
        }
        
        xo ^= a[i];
    }
    
    cout << res << endl;
    
    return 0;
}
