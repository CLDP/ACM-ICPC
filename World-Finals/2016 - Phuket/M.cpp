#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 21;

int N, M;

// start time, base priority, resource proirity, ans, position, current priority
int T[MAXN], B[MAXN], R[MAXN], ans[MAXN], S[MAXN], P[MAXN];

// locked
int L[MAXN];
vector<pair<int, int> > X[MAXN];

void clear() {
    for (int i = 0; i < N; ++i) {
        P[i] = B[i];
        if (ans[i] == -1) ans[i] = 0;
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        int C;
        cin >> T[i] >> B[i] >> C;
        for (int j = 0; j < C; ++j) {
            char Q;
            int D;
            cin >> Q >> D;
            switch (Q) {
                case 'C' : X[i].push_back(make_pair(0, D)); break;
                case 'L' : X[i].push_back(make_pair(1, D - 1)); 
                           R[D - 1] = max(R[D - 1], B[i]); break;
                case 'U' : X[i].push_back(make_pair(2, D - 1)); break;
            }
        }
        P[i] = B[i];
    }
    for (int i = 0; i < M; ++i) L[i] = -1;

    int times = 1, cnt = 0;
    while (cnt < N) {
        int a = -1, aa = -1;
        pair<int, int> Y = make_pair(-1, -1);
        for (int i = 0; i < N; ++i) {
            if (ans[i] != 0) continue;
            if (times < T[i]) continue;
            if (P[i] > aa) {
                aa = P[i];
                a = i;
            }
        }
        if (aa == -1) {
            ++times;
            continue;
        }
        pair<int, int> &XX = X[a][S[a]];

        if (XX.first == 0) {
            ++times;
            --XX.second;
            if (XX.second == 0) {
                ++S[a];
                if (S[a] == X[a].size()) {
                    ++cnt;
                    ans[a] = times;
                }
            }
            clear();
        } else
        if (XX.first == 2) {
            ++S[a];
            L[XX.second] = -1;
            if (S[a] == X[a].size()) {
                ++cnt;
                ans[a] = times;
            }
            clear();
        } else {
            int b = XX.second, temp = 0;
            for (int i = 0; i < M; ++i) {
                if (L[i] == a) continue;
                if (R[i] >= P[a] && L[i] != -1) {
                    P[L[i]] = max(P[L[i]], P[a]);
                    ++temp;
                }
            }
            if (temp == 0) {
                L[XX.second] = a;
                ++S[a];
                if (S[a] == X[a].size()) {
                    ++cnt;
                    ans[a] = times;
                }
                clear();
            } else {
                ans[a] = -1;
            }
        }
    }
    for (int i = 0; i < N; ++i) cout << ans[i] << endl;
    return 0;
}
