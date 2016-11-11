#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

long long x[15][15];
unordered_set<long long> S[14];

int main() {
    int N;
    long long L;
    cin >> N >> L;
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < N; ++j) cin >> x[i][j];
     
    if (N <= 5) {
        vector<int> X;
        for (int i = 0; i < N; ++i) X.push_back(i);
        bool flag = false;
        do {
            long long temp = x[X[N - 1]][X[0]];
            for (int i = 0; i < N - 1; ++i) temp += x[X[i]][X[i + 1]];
            if (temp == L) flag = true;
        } while (next_permutation(X.begin(), X.end()));
        if (flag) {
            cout << "possible" << endl;
        } else {
            cout << "impossible" << endl;
        }
        return 0;
    }
    
    int A = N / 2, B = N - 1 - A;
    vector<bool> X(B, 0);
    for (int i = 0; i < A; ++i) X.push_back(1);
    
    bool ans = false;
    
    do {
        vector<int> Y;
        for (int i = 0; i < 14; ++i) S[i].clear();
        
        for (int i = 0; i < A + B; ++i) {
            if (X[i]) Y.push_back(i + 1);
        }
        
        do {
            long long temp = x[0][Y[0]];
            for (int i = 0; i < A - 1; ++i) temp += x[Y[i]][Y[i + 1]];
            S[Y[A - 1]].insert(temp);
        } while (next_permutation(Y.begin(), Y.end()));
        
        for (int i = 0; i < A + B; ++i) {
            if (!X[i]) continue;
            
            Y.clear();
            for (int j = 0; j < A + B; ++j)
             if (!X[j]) Y.push_back(j + 1);
            
            do {
                long long temp = x[i + 1][Y[0]];
                for (int j = 0; j < B - 1; ++j) temp += x[Y[j]][Y[j + 1]];
                temp += x[Y[B - 1]][0];
                if (S[i + 1].find(L - temp) != S[i + 1].end()) {
                    ans = true;
                    break;
                }
                if (ans) break;
            } while (next_permutation(Y.begin(), Y.end()));
            if (ans) break;
        }
        if (ans) break;
    } while (next_permutation(X.begin(), X.end()));
    
    if (ans) cout << "possible" << endl; else cout << "impossible" << endl;
    
    return 0;
}
