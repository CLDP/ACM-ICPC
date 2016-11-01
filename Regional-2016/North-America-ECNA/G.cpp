#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

long long ans = 0;
long long f[100];
vector<int> X[3];


int main() {
    f[1] = 1;
    for (int i = 2; i <= 50; ++i) f[i] = 2 * f[i - 1] + 1;

    for (int i = 0; i < 3; ++i) {
        int M, S;
        cin >> M;
        for (int j = 0; j < M; ++j) {
            cin >> S;
            X[i].push_back(S);
        }
    }
    int N = X[0].size() + X[1].size() + X[2].size();
    while (N > 0) {
        int T = -1;
        if (X[0].size() > 0 && X[0][0] == N) T = 0;
        if (X[2].size() > 0 && X[2][0] == N) T = 2;
        if (T == -1) {
            cout << "No" << endl;
            return 0;
        }
        X[T].erase(X[T].begin());
        --N;
        swap(X[1], X[2 - T]);
        if (T == 0) ans += f[N] + 1;
    }
    cout << ans << endl;
    return 0;
}
