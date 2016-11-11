#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

set<int> S;
int N;
int x[1010];
map<int, int> CC;
unordered_map<int, bool> SS;

bool DP(int a, int k) {
    if (SS.find(a) != SS.end()) return SS[a];
    if (k == N) {
        return SS[a] = (__builtin_popcount(a) == 1);
    }
    vector<int> X;
    for (int i = 0; i <= 13; ++i) {
        if (a & (1 << i)) X.push_back(i);
    }
    for (int i = 14; i < 27; ++i) {
        if (a & (1 << i)) X.push_back(26 - i); 
    }
    int M = X.size();
    
    if (M == 0) {
        SS[a] = DP(1 << x[k], k + 1);
        return SS[a];
    }
    
    int P = 0;
    for (int i = 1; i < M; ++i) {
        if (X[i - 1] < X[i]) P = i;
    }
    
    SS[a] = false;
    if (x[k] <= X[0]) {
        int j = 0, T = x[k];
        for (j = 0; j < X.size(); ++j) {
            if (T != X[j]) break;
            ++T;
        }
        int A = 0;
        if (j < X.size() && T < X[j]) A += (1 << T); else A += (1 << (26 - T));
        for (int i = j; i < X.size(); ++i) {
            if (i < P) A += (1 << X[i]); else A += (1 << (26 - X[i]));
        }
        SS[a] |= DP(A, k + 1);
    }
    if (SS[a]) return true;
    
    if (x[k] <= X[M - 1]) {
        int j = M - 1, T = x[k];
        for (j = M - 1; j >= 0; --j) {
            if (T != X[j]) break;
            ++T;
        }
        int A = 0;
        if (j >= 0 && T < X[j]) A += (1 << (26 - T)); else A += (1 << T);
        for (int i = 0; i <= j; ++i) {
            if (i < P) A += (1 << X[i]); else A += (1 << (26 - X[i]));
        }
        SS[a] |= DP(A, k + 1);
    }
    if (SS[a]) return true;
    
    // Put on the left, only goes down
    if (P == 0 && x[k] > X[0]) {
        int A = (1 << (26 - x[k]));
        for (int i = 0; i < X.size(); ++i) A += (1 << (26 - X[i]));
        SS[a] |= DP(A, k + 1);
    }
    if (SS[a]) return true;
    
    // Put on the right, only goes up
    if (M - P == 0 && x[k] > X[M - 1]) {
        int A = (1 << x[k]);
        for (int i = 0; i < X.size(); ++i) A += (1 << X[i]);
        SS[a] |= DP(A, k + 1);
    }
    return SS[a];
}


bool DPT(int a, int k) {
    if (k == N) return 0;
    vector<int> X;
    for (int i = 0; i <= 13; ++i) {
        if (a & (1 << i)) X.push_back(i);
    }
    for (int i = 14; i < 27; ++i) {
        if (a & (1 << i)) X.push_back(26 - i); 
    }
    int M = X.size();
    
    if (M == 0) {
        printf("l");
        DPT(1 << x[k], k + 1);
        return 0;
    }
    
    int P = 0;
    for (int i = 1; i < M; ++i) {
        if (X[i - 1] < X[i]) P = i;
    }
    
    if (x[k] <= X[0]) {
        int j = 0, T = x[k];
        for (j = 0; j < X.size(); ++j) {
            if (T != X[j]) break;
            ++T;
        }
        int A = 0;
        if (j < X.size() && T < X[j]) A += (1 << T); else A += (1 << (26 - T));
        for (int i = j; i < X.size(); ++i) {
            if (i < P) A += (1 << X[i]); else A += (1 << (26 - X[i]));
        }
        if (SS[A]) {
            printf("l");
            DPT(A, k + 1);
            return 0;
        }
    }
    
    if (x[k] <= X[M - 1]) {
        int j = M - 1, T = x[k];
        for (j = M - 1; j >= 0; --j) {
            if (T != X[j]) break;
            ++T;
        }
        int A = 0;
        if (j >= 0 && T < X[j]) A += (1 << (26 - T)); else A += (1 << T);
        for (int i = 0; i <= j; ++i) {
            if (i < P) A += (1 << X[i]); else A += (1 << (26 - X[i]));
        }
        if (SS[A]) {
            printf("r");
            DPT(A, k + 1);
            return 0;
        }
    }
    
    // Put on the left, only goes down
    if (P == 0 && x[k] > X[0]) {
        int A = (1 << (26 - x[k]));
        for (int i = 0; i < X.size(); ++i) A += (1 << (26 - X[i]));
        if (SS[A]) {
            printf("l");
            DPT(A, k + 1);
            return 0;
        }
    }
    
    // Put on the right, only goes up
    if (M - P == 0 && x[k] > X[M - 1]) {
        int A = (1 << x[k]);
        for (int i = 0; i < X.size(); ++i) A += (1 << X[i]);
        if (SS[A]) {
            printf("r");
            DPT(A, k + 1);
            return 0;
        }
    }
    return 0;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < 15; ++i) CC[1 << i] = i;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
            x[i] = CC[x[i]];
        }
        SS.clear();
        if (DP(0, 0)) {
            DPT(0, 0);
            printf("\n");
        } else {
            cout << "no" << endl;
        }
    }
    return 0;
}
