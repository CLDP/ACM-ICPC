#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

bool compare(const pair<LL, LL> &A, const pair<LL, LL> &B) {
    return A.second > B.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<pair<LL, LL> > X, Y;
    for (int i = 0; i < N; ++i) {
        LL a, b;
        cin >> a >> b;
        if (a <= b) 
            X.push_back(make_pair(a, b));
        else
            Y.push_back(make_pair(a, b));
    }
    sort(X.begin(), X.end());
    LL ans = 0, rem = 0;
    for (int i = 0; i < X.size(); ++i) {
        ans = max(ans, X[i].first - rem);
        rem += X[i].second - X[i].first;
    }
    sort(Y.begin(), Y.end(), compare);
    LL temp = 0;
    for (int i = 0; i < Y.size(); ++i) {
        if (rem >= Y[i].first) {
            rem -= Y[i].first - Y[i].second;
        } else {
            ans = max(ans, temp + Y[i].first - rem);
            if (rem >= Y[i].first - Y[i].second) {
                rem -= Y[i].first - Y[i].second;
            } else {
                Y[i].first -= rem;
                rem = 0;
                temp += Y[i].first - Y[i].second;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
