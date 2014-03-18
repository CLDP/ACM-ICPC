#include <string>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 100001;

int f[MAXN];

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        int P = 0, M;
        string S;
        vector<pair<int, int> > X;
        for (int i = 0; i < N; ++i) {
            cin >> S >> M;
            if (S == "COLLECT") continue;
            if (S == "PAY") {
                P += M;
            } else {
                if (P && !X.empty()) {
                    X.push_back(make_pair(2, P));
                }
                if (S == "IN")
                    X.push_back(make_pair(0, M));
                else
                    X.push_back(make_pair(1, M));
                P = 0;
            }
        }
        
        memset(f, 0, sizeof(f));
        int delta = 0, ans = 0;
        P = 0;
        for (int i = 0; i < X.size(); ++i) {
            if (X[i].first == 0) delta += X[i].second;
            if (X[i].first == 1) delta -= X[i].second;
            if (ans > delta) ans = delta;
            if (X[i].first != 2) continue;
            ++P;
            for (int j = 1; j <= X[i].second; ++j)
             if (j > delta && X[i].second % j == 0) ++f[j - delta];
        }
        if (P == 0) {
            cout << "SIZE >= " << 1 - ans << endl;
        } else {
            int k = 0;
            for (int i = 1 - ans; i < MAXN; ++i)
             if (f[i] == P) {
                 if (k) cout << " ";
                 k = i;
                 cout << k;
             }
            if (!k) cout << "IMPOSSIBLE";
            cout << endl;
        }
    }
    return 0;
}
