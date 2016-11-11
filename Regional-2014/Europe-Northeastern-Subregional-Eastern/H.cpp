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

int f[10100];

int main() {
    int N;
    string P;
    cin >> N >> P;
    vector<pair<int, char> > X;
    for (int i = 0; i < N + N; ++i) {
        X.push_back(make_pair(i, P[i]));
    }
    int T = 0;
    for (int i = 0; i < N + N; ++i) {
        if (X[i].second >= 'a') {
            ++T;
            X[i].first = T;
        } 
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N + N - i - i - 1; ++j) {
            if (abs(X[j].second - X[j + 1].second) == 32) {
                if (X[j].second >= 'a') {
                    f[X[j + 1].first] = X[j].first;
                } else {
                    f[X[j].first] = X[j + 1].first;
                }
                X.erase(X.begin() + j, X.begin() + j + 2);
                break;
            }
        }
    }
    
    vector<int> ans;
    for (int i = 0; i < N + N; ++i) {
        if (f[i] == 0) continue;
        ans.push_back(f[i]);
    }
    
    if (ans.size() != N) {
        cout << "Impossible" << endl;
    } else {
        for (int i = 0; i < N; ++i) printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}
