#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    long long tot;
    int ind;
};

vector<node> x[20];

bool compare(const node &n1, const node &n2) {
    return n1.tot > n2.tot;
}

long long base[20];

int main() {
    long long xx, n;
    node tmpN;
    long long k, q;
    cin >> xx >> n;
    
    base[0] = 1;
    for (int i = 1; i < 20; ++i) base[i] = base[i - 1] * 10;
    
    for (int i = 0; i < n; ++i) {
        cin >> k >> q;
        tmpN.tot = base[k] * q;
        tmpN.ind = i + 1;
        x[k].push_back(tmpN);
    }
    
    for (int i = 0; i < 19; ++i)
        sort(x[i].rbegin(), x[i].rend(), compare);
    
    vector<int> bn;
    int res = 0;
    
    k = 1;
    q = 10;
    while (xx % q == 0) {
        ++k;
        if (k < 19)
            q *= 10;
        else
            break;
    }
    while (xx > 0) {
        long long best = 0;
        int tind;
        for (int i = 0; i < k; ++i)
         if (x[i].size() > 0)
          if (x[i][x[i].size() - 1].tot > best) {
              best = x[i][x[i].size() - 1].tot;
              tind = i;
          }
        if (best == 0) break;
        
        long long newxx = xx - best;
        while (xx / q != newxx / q) {
            ++k;
            if (k < 19)
                q *= 10;
            else
                break;
        }
        xx = newxx;
        bn.push_back(x[tind][x[tind].size() - 1].ind);
        x[tind].pop_back();
    }
    
    if (xx <= 0) {
        cout << bn.size() << endl << bn[0];
        for (int i = 1; i < bn.size(); ++i) cout << " " << bn[i];
        cout << endl;
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}
