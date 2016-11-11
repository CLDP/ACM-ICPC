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

vector<int> c[1005];
vector<int> un;
pair<int, int> res[1005];

int main() {
    int n, k;
    
    cin >> k >> n;
    for (int i = 0; i < k; ++i) {
        int j;
        cin >> j;
        if (j == -1)
            un.push_back(i);
        else
            c[j].push_back(i);
    }
    
    int m = k / n;
    while (true) {
        int maxs = 0, maxsInd = -1, mins = k + 1, minsInd = -1;
        for (int i = 1; i <= n; ++i) {
            if (c[i].size() == 0) continue;
            if (c[i].size() > maxs) {
                maxs = c[i].size();
                maxsInd = i;
            }
            if (c[i].size() <= mins) {
                mins = c[i].size();
                minsInd = i;
            }
        }
        if (maxsInd == -1) break;
        if (maxsInd == minsInd) {
            int cur = m;
            while ((c[maxsInd].size() > 0) && (cur > 0)) {
                --cur;
                res[c[maxsInd].back()] = make_pair(maxsInd, 1);
                c[maxsInd].pop_back();
            }
            while (cur > 0) {
                --cur;
                res[un.back()] = make_pair(maxsInd, 1);
                un.pop_back();
            }
        } else {
            int cur = m;
            while ((c[minsInd].size() > 0) && (cur > 0)) {
                --cur;
                res[c[minsInd].back()] = make_pair(maxsInd, minsInd);
                c[minsInd].pop_back();
            }
            while ((c[maxsInd].size() > 0) && (cur > 0)) {
                --cur;
                res[c[maxsInd].back()] = make_pair(maxsInd, minsInd);
                c[maxsInd].pop_back();
            }
            while (cur > 0) {
                --cur;
                res[un.back()] = make_pair(maxsInd, minsInd);
                un.pop_back();
            }
        }
    }
    
    for (int i = 1; i <= n; ++i)
        while (!c[i].empty()) {
            res[c[i].back()] = make_pair(i, i);
            c[i].pop_back();
        }
    
    while (!un.empty()) {
        res[un.back()] = make_pair(1, 1);
        un.pop_back();
    }
    
    cout << "Yes" << endl;
    for (int i = 0; i < k; ++i) cout << res[i].first << " " << res[i].second << endl;

    return 0;
}
