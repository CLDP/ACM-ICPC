#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int cnt[100005];
vector<int> ps[100005];

int main() {
    int t;
    
    for (int i = 2; i < 100002; ++i)
        if (ps[i].size() == 0)
            for (int j = i; j < 100002; j += i)
                ps[j].push_back(i);
    
    scanf("%d", &t);
    vector<int> tmp;
    tmp.reserve(130);
    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            tmp.clear();
            for (int j = 0; j < ps[a[i]].size(); ++j) {
                int s = tmp.size();
                for (int k = 0; k < s; ++k)
                    tmp.push_back(ps[a[i]][j] * tmp[k]);
                tmp.push_back(ps[a[i]][j]);
            }
            for (int j = 0; j < tmp.size(); ++j) ++cnt[tmp[j]];
        }
        
        long long z = 0;
        for (int i = 0; i < n; ++i) {
            tmp.clear();
            for (int j = 0; j < ps[a[i]].size(); ++j) {
                int s = tmp.size();
                for (int k = 0; k < s; ++k)
                    tmp.push_back(ps[a[i]][j] * tmp[k]);
                tmp.push_back(ps[a[i]][j]);
            }
            long long x = 0;
            for (int j = 0; j < tmp.size(); ++j) {
                if (j % 2 == 0)
                    x += cnt[tmp[j]] - 1;
                else
                    x = x - (cnt[tmp[j]] - 1);
            }
            z += x * (n - x - 1);
        }
        
        z = z / 2;
        long long res = n;
        res = res * (res - 1) * (res - 2) / 6 - z;
        
        cout << res << endl;
    }
    
    return 0;
}
