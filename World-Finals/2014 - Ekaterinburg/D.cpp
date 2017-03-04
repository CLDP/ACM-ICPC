#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 26;

vector<int> X[MAXN];
int ans[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int M;
        cin >> M;
        for (int j = 0; j < M; ++j) {
            string P;
            int temp = 0;
            cin >> P;
            for (int k = 0; k < P.size(); ++k) temp |= (1 << (P[k] - 'a'));
            X[i].push_back(temp);
        }
    }

    for (int i = 0; i < N; ++i) {
        int state = (1 << i), step = 0;
        for (int step = 1; ; ++step) {
            int update = 0;
            for (int j = 0; j < N; ++j) {
                if ((1 << j) & state) continue;
                for (int k = 0; k < X[j].size(); ++k) {
                    if ((state & X[j][k]) == X[j][k]) {
                        update |= (1 << j);
                        ans[j][i] = step;
                    }
                }
            }
            if (update == 0) break;
            state |= update;
        }
        for (int j = 0; j < N; ++j) {
            if (j == i) continue;
            if (ans[j][i] == 0) ans[j][i] = -1;
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}
