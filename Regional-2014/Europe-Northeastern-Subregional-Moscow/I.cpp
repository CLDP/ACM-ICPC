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

bool p[300005];
vector<int> ps;

int main() {
    int n;
    
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        if (!p[i]) {
            ps.push_back(i);
            for (int j = i + i; j <= n; j += i) p[j] = true;
        }
    }
    
    int ind = 0, left = 42;
    long long base = 1, l = 0;
    while (left <= ps.size()) {
        --left;
        cout << "2" << endl;
        cout.flush();
        string c;
        cin >> c;
        if (c == "OK") return 0;
        base *= 2;
        if (c == "<")
            l = l * 2 + 1;
        else
            l = l * 2;
        for (int i = 0; i < ps.size(); ++i) {
            if (ps[i] * l / base >= ps[i] * (l + 1) / base) {
                ps[i] = ps[ps.size() - 1];
                ps.pop_back();
                --i;
            }
        }
    }
    
    for (int i = 0; i < ps.size(); ++i) {
        cout << ps[i] << endl;
        cout.flush();
        string c;
        cin >> c;
        if (c == "OK") return 0;
    }

    return 0;
}
