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


int main() {
    string P, Q;
    cin >> P >> Q;
    int ans = 0, i, j;
    for (i = 0, j = 0; i < P.size() && j < Q.size(); ) {
        ++ans;
        if (P[i] == 'L' && Q[j] == 'L') {
            ++i;
            ++j;
        } else
        if (P[i] == 'L') {
            ++j;
        } else 
        if (Q[j] == 'L') {
            ++i;
        } else {
            ++i;
            ++j;
        }
    }
    cout << ans + P.size() + Q.size() - i - j << endl;
    return 0;
}
