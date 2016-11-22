#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    double w, u, v, t1, t2;
    cin >> N >> w >> u >> v >> t1 >> t2;
    vector<pair<double, double> > T;
    for (int i = 0; i < N; ++i) {
        char C;
        cin >> C >> M;
        double c = w * i / v, d = w * (i + 1) / v;
        for (int j = 0; j < M; ++j) {
            double a, b;
            cin >> a >> b;
            if (C == 'E') b = -b;
            T.push_back(make_pair(b / u - d, (a + b) / u - c));
        }
    }
    sort(T.begin(), T.end());
    if (T.size() == 0) {
        cout << t2 - t1 << endl;
        return 0;
    }

    double L = T[0].first, R = T[0].second;
    double ans = max(t1, min(L, t2)) - t1;
    for (int i = 1; i < T.size(); ++i) {
        if (T[i].first < R) {
            R = max(R, T[i].second);
        } else {
            ans = max(ans, min(t2, T[i].first) - max(R, t1));
            L = T[i].first;
            R = T[i].second;
        }
    }
    ans = max(ans, t2 - max(R, t1));
    printf("%.8lf\n", ans);

    return 0;
}
