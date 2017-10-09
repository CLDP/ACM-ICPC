#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 10010;

long long x[MAXN];
long long a[MAXN], b[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, K;
    long long T1, T2;
    cin >> N >> K >> T1 >> T2;
    for (int i = 0; i < N; ++i) cin >> x[i];
    for (int i = 0; i < K; ++i) cin >> a[i] >> b[i];

    vector<pair<long long, long long> > X;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            long long A = max(T1, a[i] - x[j]);
            long long B = min(b[i] - x[j], T2);
            if (A > B) continue;
            X.push_back(make_pair(A, B));
        }
    }
    if (X.size() == 0) {
        cout << 1 << endl;
        return 0;
    }

    sort(X.begin(), X.end());

    long long ans = X[0].first - T1;
    long long R = X[0].second;
    for (int i = 0; i < X.size(); ++i) {
        if (X[i].first <= R) {
            R = max(R, X[i].second);
            continue;
        }
        ans += X[i].first - R;
        R = X[i].second;
    }

    ans += T2 - R;
    cout << fixed << setprecision(8) << 1.0 * ans / (T2 - T1) << endl;

    return 0;
}
