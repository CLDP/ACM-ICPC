#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int N, K;
int x[MAXN], y[MAXN], b[MAXN];

bool check(int xx, int i, pair<int, int> &temp) {
    int dx = abs(xx - x[i]);
    if (dx > 500) return false;
    if (dx * dx * dx > b[i]) return false;

    int L = 0, R = 500;
    while (L + 1 < R) {
        int mid = (L + R) / 2;
        if (dx * dx * dx + mid * mid * mid > b[i]) R = mid; else L = mid;
    }

    temp = make_pair(max(0, y[i] - L), min(N, y[i] + L));
    return true;
}

void update(long long &ans, int xx) {
    vector<pair<int, int> > S;
    for (int i = 0; i < K; ++i) {
        pair<int, int> temp;
        if (check(xx, i, temp)) S.push_back(temp);
    }
    if (S.empty()) return ;
    sort(S.begin(), S.end());

    ans -= S[0].second - S[0].first + 1;
    int R = S[0].second;
    for (int i = 1; i < S.size(); ++i) {
        if (S[i].first <= R) {
            if (S[i].second > R) {
                ans -= S[i].second - R;
                R = S[i].second;
            }
            continue;
        }

        ans -= S[i].second - S[i].first + 1;
        R = S[i].second;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> N >> K;
    if (K == 0) {
        cout << 1LL * (N + 1) * (N + 1) << endl;
        return 0;
    }

    for (int i = 0; i < K; ++i) cin >> x[i] >> y[i] >> b[i];

    set<int> S;
    long long ans = 1LL * (N + 1) * (N + 1);
    for (int i = 0; i < K; ++i) {
        for (int j = -500; j <= 500; ++j) {
            if (abs(j * j * j) > b[i]) continue;
            if (S.find(x[i] + j) != S.end()) continue;
            update(ans, x[i] + j);
            S.insert(x[i] + j);
        }
    }

    cout << ans << endl;

    return 0;
}
