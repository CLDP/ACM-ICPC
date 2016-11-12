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

vector<long long> k;
multiset<long long> l;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    long long n, s, t;
    cin >> n >> s >> t;
    k.resize(n);
    for (int i = 0; i < n; ++i) cin >> k[i];
    
    sort(k.begin(), k.end());
    
    long long worst = 0, best = (s + t) * n;
    long long tot = 0;
    
    for (int i = 0; i < n; ++i) {
        l.clear();
        for (int j = 0; j < n; ++j) l.insert(k[j]);
        long long cur = 0, pos = k[i];
        l.erase(l.find(k[i]));
        cur = t;
        while (!l.empty()) {
            long long next = (pos + t) % s;
            long long wait = next;
            if (next > *l.rbegin())
                next = *l.begin();
            else 
            if (l.find(next) == l.end())
                next = *l.upper_bound(next);
            if (next >= wait)
                wait = next - wait;
            else
                wait = next - wait + s;
            cur += t + wait;
            pos = next;
            l.erase(l.find(pos));
        }
        if (cur < best) best = cur;
        long long num = 0;
        if (i == 0)
            num = k[0] + s - k[n-1];
        else
            num = k[i] - k[i-1];
        if ((num > 0) && (cur + num - 1 > worst)) worst = cur + num - 1;
        tot += cur * num + num * (num - 1) / 2;
    }
    
    long long d = gcd(tot, s);
    tot = tot / d;
    s = s / d;
    
    cout << best << endl;
    cout << worst << endl;
    cout << tot << "/" << s << endl;

    return 0;
}
