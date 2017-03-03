#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2010;

struct node {
    long long x1, x2, y;
};

struct event {
    // A = dy, B = dx
    long long A, B;
    long long C;
    event() {}
    event(long long _A, long long _B, long long _C) {
        A = _A;
        B = _B;
        C = _C;
        if (B == 0) {
            A = abs(A);
            return ;
        }
        if (A < 0) {
            A = -A;
            B = -B;
        }
    }
    bool operator < (const event &T) const {
        if (B == 0) return T.B < 0 || (T.B == 0 && C > 0 && T.C < 0);
        if (T.B == 0) return B > 0 || (B == 0 && C > 0 && T.C < 0);
        if (T.B * B < 0) return B > 0;
        return A * T.B < T.A * B || (A * T.B == T.A * B && C > 0 && T.C < 0);
    }
};

int N;
node X[MAXN];

long long deal(long long x, long long y) {
    long long ans = 0;
    vector<event> S;
    for (int i = 0; i < N; ++i) {
        if (X[i].y == y) continue;
        if (X[i].y > y) {
            S.push_back(event(X[i].y - y, x - X[i].x1, X[i].x2 - X[i].x1));
            S.push_back(event(X[i].y - y, x - X[i].x2, X[i].x1 - X[i].x2));
        } else {
            S.push_back(event(X[i].y - y, x - X[i].x2, X[i].x2 - X[i].x1));
            S.push_back(event(X[i].y - y, x - X[i].x1, X[i].x1 - X[i].x2));
        }
    }
    sort(S.begin(), S.end());
    long long temp = 0;
    for (int i = 0; i < S.size(); ++i) {
        temp += S[i].C;
        ans = max(ans, temp);
    }
    return ans;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> X[i].x1 >> X[i].x2 >> X[i].y;
        if (X[i].x1 > X[i].x2) swap(X[i].x1, X[i].x2);
    }
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        ans = max(ans, deal(X[i].x1, X[i].y) + X[i].x2 - X[i].x1);
        ans = max(ans, deal(X[i].x2, X[i].y) + X[i].x2 - X[i].x1);
    }
    cout << ans << endl;
    return 0;
}
