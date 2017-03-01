#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int X[MAXN], Y[MAXN], C[MAXN];
vector<int> S;


int main() {
    ios_base::sync_with_stdio(false);
    int N, M, sum = 0;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> X[i];
        sum += X[i];
    }
    for (int i = 0; i < M; ++i) {
        cin >> Y[i];
        ++C[Y[i]];
    }
    if (M > sum) {
        int T = 1;
        while (sum * T < M) ++T;
        for (int i = 1; i <= N; ++i) X[i] *= T;
        sum *= T;
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = C[i] + 1; j <= X[i]; ++j) {
            S.push_back(ceil(1.0 * j * sum / X[i]));
        }
    }
    sort(S.begin(), S.end());
    for (int i = 0; i < S.size(); ++i) {
        if (i + M < S[i]) continue;
        cout << S[i] - M - 1 << endl;
        return 0;
    }
    cout << "forever" << endl;
    return 0;
}
