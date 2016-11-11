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
    int times;
    cin >> times;
    for (int tt = 1; tt <= times; ++tt) { 
        int N;
        cin >> N;
        vector<pair<int, int> > X;
        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            X.push_back(make_pair(a, b));
        } 
        sort(X.begin(), X.end());
        double ans = 0;
        for (int i = 1; i < N; ++i) 
            ans = max(ans, 1.0 * abs(X[i].second - X[i - 1].second) / (X[i].first - X[i - 1].first));
        printf("Case #%d: %.2lf\n", tt, ans);
    }
    return 0;
}
