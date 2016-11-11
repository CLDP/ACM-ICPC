#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;


int main() {
    int n, res = 0;
    cin >> n;
    unordered_map<string, int> m;
    
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (m.find(s) == m.end())
            m[s] = 1;
        else
            ++m[s];
    }
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (m[s] > 0) {
            --m[s];
            ++res;
        }
    }
    
    cout << res << endl;

    return 0;
}
