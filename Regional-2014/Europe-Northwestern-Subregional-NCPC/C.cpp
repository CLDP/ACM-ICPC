#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

vector<long long> res;
const long long p = 100000;

void mult(long long v) {
    long long c = 0;
    for (int i = 0; i < res.size(); ++i) {
        res[i] = res[i] * v + c;
        c = res[i] / p;
        res[i] = res[i] % p;
    }
    if (c > 0) res.push_back(c);
}

void div(long long v) {
    long long r = 0;
    for (int i = res.size() - 1; i >= 0; --i) {
        res[i] += r * p;
        r = res[i] % v;
        res[i] = res[i] / v;
    }
}


int main() {
    long long n;
    cin >> n;
    ++n;
    
    res.push_back(1);
    for (int i = 1; i <= n; ++i) {
        mult(n+i);
        div(i);
    }
    
    div(n + 1);

    while (res[res.size() - 1] == 0) res.pop_back();
    cout << res[res.size() - 1];
    int i = res.size() - 1;
    for (i--; i >= 0; i--) {
        int pp = p / 10;
        int v = res[i];
        while (pp >= 1) {
            cout << v / pp;
            v = v % pp;
            pp = pp / 10;
        }
    }
    cout << endl;

    return 0;
}
