#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct event {
    int x, y, z, id;
    bool operator < (const event &B) const {
        if (x != B.x) return x < B.x;
        if (z != B.z) return z < B.z;
        return y < B.y;
    }
};

struct interval {
    int a, b, c, d;
    interval(int _a, int _b, int _c, int _d): a(_a), b(_b), c(_c), d(_d) {}
    bool operator < (const interval &B) const {
        if (c != B.c) return c < B.c;
        if (d != B.d) return d < B.d;
        if (a != B.a) return a < B.a;
        return b < B.b;
    }
};

bool compare(const event &A, const event &B) {
    return A.id < B.id;
}

bool intersect(pair<int, int> A, pair<int, int> B) {
    if (A.first < B.first && B.second < A.second) return false;
    if (B.first < A.first && A.second < B.second) return true;
    if (A.second < B.first || B.second < A.first) return false;
    return true;
}


event X[MAXN + MAXN];
int ans[MAXN];


int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> X[i].x >> X[i].y;
        X[i].z = -1;
        X[i].id = i;
    }
    for (int i = 0; i < N; ++i) {
        cin >> X[i + N].x >> X[i + N].y;
        X[i + N].z = 1;
        X[i + N].id = i + N;

    }
    sort(X, X + N + N);

    set<pair<int, int> > S;
    for (int i = 0; i < N + N; ++i) {
        if (X[i].z == -1) {
            S.insert(make_pair(X[i].y, X[i].id));
        } else {
            auto iter = S.upper_bound(make_pair(X[i].y + 1, -1));
            if (S.empty() || iter == S.begin()) {
                cout << "syntax error" << endl;
                return 0;
            }
            --iter;
            ans[iter->second] = X[i].id;
            S.erase(iter);
        }
    }
    sort(X, X + N + N, compare);

    vector<interval> Y;
    for (int i = 0; i < N; ++i) {
        Y.push_back(interval(X[i].y, X[ans[i]].y, X[i].x, -1));
        Y.push_back(interval(X[i].y, X[ans[i]].y, X[ans[i]].x, 1));
    }
    sort(Y.begin(), Y.end());
    for (int i = 0; i < N + N; ++i) {
        if (i > 0 && Y[i - 1].c == Y[i].c && Y[i - 1].d == Y[i].d) {
            if (Y[i - 1].b >= Y[i].a) {
                cout << "syntax error" << endl;
                return 0;
            }
        }
    }

    set<pair<int, int> > C;
    for (int i = 0; i < N + N; ++i) {
        if (Y[i].d == 1) C.erase(make_pair(Y[i].a, Y[i].b)); 
        auto iter = C.lower_bound(make_pair(Y[i].a, -1));
        if (iter != C.begin()) {
            --iter;
            if (intersect(*iter, make_pair(Y[i].a, Y[i].b))) {
                cout << "syntax error" << endl;
                return 0;
            }
            ++iter;
        }
        if (iter != C.end()) {
            if (intersect(*iter, make_pair(Y[i].a, Y[i].b))) {
                cout << "syntax error" << endl;
                return 0;
            }
        }
        if (Y[i].d == -1) C.insert(make_pair(Y[i].a, Y[i].b));
    }

    for (int i = 0; i < N; ++i) cout << ans[i] + 1 - N << endl;

    return 0;
}
