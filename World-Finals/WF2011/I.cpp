#include <cstdio>
#include <vector>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int MAXM = 4100000;

int nn, N;
int x[MAXN], y[MAXN];

struct event {
    int x, y, type;  // 0 -- insert, 1 -- delete
    event() {}
    event(int _x, int _y, int _type) : x(_x), y(_y), type(_type) {}
    bool operator < (event const &B) const {
        if (x != B.x) return x < B.x;
        return type < B.type;
    }
};


bool check(int L) {
    vector<event> X;
    for (int i = 0; i < N; ++i) {
        X.push_back(event(x[i] - L, y[i], 0));
        X.push_back(event(x[i] + L + 1, y[i], 1));
        if (-L <= x[i] - L - 1 && x[i] - L - 1 <= L) X.push_back(event(x[i] - L - 1, 0, 2));
        if (-L <= x[i] + L + 1 && x[i] + L + 1 <= L) X.push_back(event(x[i] + L + 1, 0, 2));
        if (-L <= x[i] - L && x[i] - L <= L) X.push_back(event(x[i] - L, 0, 2));
        if (-L <= x[i] + L && x[i] + L <= L) X.push_back(event(x[i] + L, 0, 2));
    }
    sort(X.begin(), X.end());
    
    multiset<int> S;
    for (int i = 0; i < X.size(); ++i) {
        if (X[i].type == 0) {
            S.insert(X[i].y);
            continue;
        }
        if (X[i].type == 1) {
            S.erase(S.find(X[i].y));
            continue;
        }
        if (X[i].type == 2) {
            multiset<int>::iterator iter = S.lower_bound(0);
            if (iter == S.end()) return true;
            if (*iter == 0) continue;
            int B = *iter - L - 1;
            if (iter == S.begin()) return true;
            --iter;
            int A = *iter + L + 1;
            if (B < A) continue;
            return true;
        }
    }
    return false;
}

int main() {
    int times = 0;
    while (cin >> N) {
        if (N == -1) break;
        for (int i = 0; i < N; ++i) scanf("%d%d", &x[i], &y[i]);
        
        cout << "Case " << ++times << ": ";
        if (N == 0 || check(1000000)) {
            cout << "never" << endl;
            continue;
        }
        
        int L = 0, R = 1000000;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            if (check(mid)) L = mid; else R = mid;
        }
        cout << R << endl;
    }
    return 0;
}
