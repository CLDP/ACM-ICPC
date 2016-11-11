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

vector<int> p;

void init(int a, int b) {
    p.push_back(a);
    if (a >= 100) return;
    
    if ((b % 3 != 0) || (b == 0)) init(a * 10, 0);
    if (b == 0) return;
    for (int i = b; i < 10; ++i)
        if ((b - 1) % 3 <= (i - 1) % 3) init(a * 10 + i, i);
    return;
}

int main() {
    int t;
    p.push_back(0);
    for (int i = 1; i < 10; ++i) init(i, i);
    
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        int best = 0, bd = k;
        for (int i = 0; i < p.size(); ++i)
            if (abs(p[i] - k) < bd) {
                bd = abs(p[i] - k);
                best = p[i];
            }
        cout << best << endl;
    }

    return 0;
}
