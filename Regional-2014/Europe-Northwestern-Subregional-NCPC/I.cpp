#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

long long gcd(long long a, long long b) {
    long long r = a % b;
    while (r > 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main() {
    int n;
    map<pair<long long ,long long>, vector<long long> > m;
    long long res = 0;
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pair<long long, long long> f;
        long long c;
        if (x1 == x2) {
            f.first = 1;
            f.second = 0;
            c = x1;
        } else 
        if (y1 == y2) {
            f.first = 0;
            f.second = -1;
            c = y1;
        } else {
            f.first = y2 - y1;
            f.second = x2 - x1;
            if (f.first * f.second < 0)
                f.second = abs(f.second);
            else
                f.second = -abs(f.second);
            f.first = abs(f.first);
            long long d = gcd(f.first, abs(f.second));
            f.first = f.first / d;
            f.second = f.second / d;
            c = f.first * x1 + f.second * y1;
            c = -c;
        }
        if (m.find(f) == m.end()) m[f] = vector<long long>();
        m[f].push_back(c);
    }
    
    for (map<pair<long long ,long long>, vector<long long> >::iterator it = m.begin(); it != m.end(); ++it) {
        if (it->first.second < 0) continue;
        pair<long long, long long> f;
        f.first = it->first.second;
        f.second = -it->first.first;
        if (m.find(f) == m.end()) continue;
        map<long long, long long> cnt;
        for (int i = 0; i < m[f].size(); ++i)
            for (int j = i + 1; j < m[f].size(); ++j) {
                long long d = abs(m[f][i] - m[f][j]);
                if (cnt.find(d) == cnt.end()) cnt[d] = 0;
                cnt[d] = cnt[d] + 1;
            }
        for (int i = 0; i < it->second.size(); ++i)
            for (int j = i + 1; j < it->second.size(); ++j) {
                long long d = abs(it->second[i] - it->second[j]);
                if (cnt.find(d) != cnt.end()) res += cnt[d];
            }
    }    
    cout << res << endl;

    return 0;
}
