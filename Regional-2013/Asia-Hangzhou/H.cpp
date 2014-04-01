#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
const int MAXM = 400010;
const int INF = 1000000000;

struct node {
    // type == 0 insert, 2 query, INF delete
    int a, b, c, type;
    node() {}
    node(int _a, int _b, int _c, int _type) : a(_a), b(_b), c(_c), type(_type) {}
    bool operator < (node const &B) const {
        if (a != B.a) return a < B.a;
        return type < B.type;
    }
};

int N, K, nn;
vector<int> PRIME;
vector<pair<int, int> > X;
int x[MAXN];
int Y[MAXN];
int s[MAXM];
int ans[MAXN];


int getPRIME() {
    vector<bool> z(MAXN, false);
    for (int i = 2; i < 200000; ++i) {
        if (!z[i]) {
            PRIME.push_back(i);
            int j = i;
            while (j < MAXN) {
                z[j] = true;
                j += i;
            }
        }
    }
    return 0;
}

int factor(int A, vector<int> &P) {
    P.clear();
    int M = PRIME.size();
    for (int i = 0; i < M; ++i) {
        if (A % PRIME[i] == 0) {
            P.push_back(i);
            while (A % PRIME[i] == 0) A /= PRIME[i]; 
        }
        if (A == 1) break;
        if (PRIME[i] > 1000) break;
    }
    if (A > 1) {
        int j = lower_bound(PRIME.begin(), PRIME.end(), A) - PRIME.begin();
        P.push_back(j);
    }
    return 0;
}

int getX() {
    X = vector<pair<int, int> > (N, make_pair(1, N));
    memset(Y, 0, sizeof(Y));
    for (int i = 0; i < N; ++i) {
        if (x[i] == 1) continue;
        vector<int> P;
        factor(x[i], P);
        int ll = 0;
        for (int j = 0; j < P.size(); ++j) {
            if (Y[P[j]] != 0)
                X[Y[P[j]] - 1].second = min(X[Y[P[j]] - 1].second, i);
            ll = max(ll, Y[P[j]]);
            Y[P[j]] = i + 1;
        }
        X[i].first = ll + 1;
    }
    return 0;
}

int update(int a, int b) {
    for (int i = a; i < MAXM; i += (i & -i)) s[i] += b;
    return 0;
}

int query(int a) {
    int ans = 0;
    for (int i = a; i > 0; i -= (i & -i)) ans += s[i];
    return ans;
}

int main() {
    getPRIME();
    while (scanf("%d%d", &N, &K)) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) scanf("%d", &x[i]);
        getX();
        vector<node> T;
        for (int i = 0; i < N; ++i) {
            T.push_back(node(X[i].first, i + 1, X[i].second + 1, 0));
            T.push_back(node(i + 1, i + 1, X[i].second + 1, INF));
        }
        for (int i = 0; i < K; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            T.push_back(node(a, b, 0, 2 + i));
        }
        sort(T.begin(), T.end());
        int TT = T.size();
        for (int i = 0; i < TT; ++i) {
            if (T[i].type == 0) {
                update(T[i].b, 1);
                update(T[i].c, -1);
                continue;
            }
            if (T[i].type == INF) {
                update(T[i].b, -1);
                update(T[i].c, 1);
                continue;
            }
            ans[T[i].type - 2] = query(T[i].b) - query(T[i].a - 1);
        }
        for (int i = 0; i < K; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
