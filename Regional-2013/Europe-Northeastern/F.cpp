#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;



int main() {
    freopen("fraud.in", "r", stdin);
    freopen("fraud.out", "w", stdout);
    string P;
    int N;
    cin >> P >> N;
    vector<string> ans;
    for (int i = 0; i < N; ++i) {
        bool flag = true;
        string Q;
        cin >> Q;
        if (Q.size() != P.size()) continue;
        for (int j = 0; j < P.size(); ++j) {
            if (P[j] == '*') continue;
            if (P[j] == Q[j]) continue;
            flag = false;
        }
        if (flag) ans.push_back(Q);
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) cout << ans[i] << endl;
    
    return 0;
}
