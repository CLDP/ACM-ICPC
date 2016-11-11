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

vector<int> ssa;
int decL[200005];
int incL[200005];
int x[200005];
int n;

int main() {
    freopen("improvements.in", "r", stdin);
    freopen("improvements.out", "w", stdout);
    
    cin >> n;
    
    for (int i = 0; i < n; ++i) cin >> x[i];
    
    decL[0] = 1;
    incL[0] = 1;
    ssa.clear();
    ssa.push_back(x[0]);
    
    for (int i = 1; i < n; ++i) {
        if (x[i] > ssa.back()) {
            ssa.push_back(x[i]);
            incL[i] = ssa.size();
        } else {
            int l = 0, r = ssa.size() - 1;
            while (l != r) {
                int k = (l + r) / 2;
                if (x[i] < ssa[k])
                    r = k;
                else
                    l = k + 1;
            }
            ssa[l] = x[i];
            incL[i] = l + 1;
        }
    }
    
    ssa.clear();
    ssa.push_back(x[0]);
    for (int i = 1; i < n; ++i) {
        if (x[i] < ssa.back()) {
            ssa.push_back(x[i]);
            decL[i] = ssa.size();
        } else {
            int l = 0, r = ssa.size();
            while (l != r) {
                int k = (l + r) / 2;
                if (x[i] > ssa[k])
                    r = k;
                else
                    l = k + 1;
            }
            ssa[l] = x[i];
            decL[i] = l + 1;
        }
    }
    
    int res = 0;
    for (int i = 0; i < n; ++i) res = max(res, incL[i] + decL[i] - 1);
    
    cout << res << endl;

    return 0;
}
