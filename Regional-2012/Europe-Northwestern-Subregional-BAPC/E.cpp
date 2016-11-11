#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


int main() {
    int n;
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int l = s.length();
        int m = sqrt(l);
        
        vector<vector<char> > v(m, vector<char>(m));
        int cnt = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                v[m - 1 - j][i] = s[cnt++];
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j) cout << v[i][j];
        cout << endl;
    }

    return 0;
}
