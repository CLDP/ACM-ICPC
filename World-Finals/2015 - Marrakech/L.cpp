#include <iostream>
#include <cmath>
#include <set>
using namespace std;

struct node {
    double prob;
    long long cnt;

    node() {}
    node(double _prob, long long _cnt) : prob(_prob), cnt(_cnt) {}

    bool operator < (const node &B) const {
        return prob < B.prob;
    }
};


int main() {
    int N;
    double a, b, c, d;
    cin >> N >> a >> b >> c >> d;
    long long f[21];
    f[0] = 1;
    for (int i = 1; i <= 20; ++i) f[i] = f[i - 1] * i;

    multiset<node> X;
    for (int i = 0; i <= N; ++i)
     for (int j = 0; j <= N; ++j)
      for (int k = 0; k <= N; ++k) {
          int l = N - i - j - k;
          if (l < 0) break;
          X.insert(node(pow(a, i) * pow(b, j) * pow(c, k) * pow(d, l), 
                        f[N] / f[i] / f[j] / f[k] / f[l]));
      }

    double ans = 0;
    while (X.size() > 1) {
        node T = *X.begin();
        X.erase(X.begin());
        if (T.cnt > 1) {
            X.insert(node(T.prob * 2, T.cnt / 2));
            ans += T.prob * (T.cnt / 2 * 2);
            if (T.cnt & 1) {
                X.insert(node(T.prob, 1));
            }
        } else {
            node Q = *X.begin();
            X.erase(X.begin());
            ans += T.prob + Q.prob;
            X.insert(node(T.prob + Q.prob, 1));
            if (Q.cnt > 1) X.insert(node(Q.prob, Q.cnt - 1));
        }
    }
    printf("%.6lf\n", ans);

    return 0;
}
