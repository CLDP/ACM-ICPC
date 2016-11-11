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

long long a[105];
vector<long long> mm[1005];
bool res[1005];
int rcnt;
vector<long long> uv;

bool tmp[1075];
int n, m, f, q;

void gene(vector<long long>& vv) {
    long long v = 0;
    int ind = 0;
    while (ind < m) {
        v = 0;
        for (int i = 0; i < 50; ++i) v = v * 2 + tmp[ind++];
        vv.push_back(v);
    }
}

int main() {
    freopen("filter.in", "r", stdin);
    freopen("filter.out", "w", stdout);
    
    cin >> m >> f;
    for (int i = 0; i < f; ++i) cin >> a[i];
    
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        for (int j = 0; j < m; ++j) tmp[j] = false;
        int ind = 0, si = 0;
        while (ind < m) {
            int v;
            if (s[si] <= '9')
                v = s[si] - '0';
            else
                v = s[si] - 'a' + 10;
            for (int j = 0; j < 4; ++j) {
                if (v % 2 == 1) tmp[ind] = true;
                v = v / 2;
                ++ind;
            }
            ++si;
        }
        gene(mm[i]);
    }
    
    rcnt = 0;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        long long u;
        cin >> u;
        for (int j = 0; j < m; ++j) tmp[j] = false;
        for (int j = 0; j < f; ++j) {
            long long k = (u * a[j]) % m;
            tmp[k] = true;
        }
        uv.clear();
        gene(uv);
        
        for (int j = 0; j < n; ++j) {
            bool check = true;
            for (int k = 0; k < uv.size(); ++k)
                if ((uv[k] & mm[j][k]) != uv[k]) {
                    check = false;
                    break;
                }
            if (check && !res[j]) {
                res[j] = true;
                rcnt++;
            }
        }
    }
    
    cout << rcnt;
    for (int i = 0; i < n; ++i)
        if (res[i]) cout << " " << i;
    cout << endl;

    return 0;
}
