#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 22;

vector<int> X[MAXN][MAXN];

int main() {
    int N, M, times  = 0;
    while (cin >> N >> M) {
        ++times;
        if (N == 0 && M == 0) break;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int a;
                cin >> a;
                X[i][j] = vector<int> (1, a);
            }
        }

        int L = 0, R = M - 1, U = 0, B = N - 1;
        string P;
        getline(cin, P);
        getline(cin, P);
        for (int t = 0; t < P.size(); ++t) {
            if (P[t] == 'T') {
                for (int j = L; j <= R; ++j) {
                    for (int i = X[U][j].size() - 1; i >= 0; --i) {
                        X[U + 1][j].push_back(-X[U][j][i]);
                    }
                }
                ++U;
            } 
            if (P[t] == 'B') {
                for (int j = L; j <= R; ++j) {
                    for (int i = X[B][j].size() - 1; i >= 0; --i) {
                        X[B - 1][j].push_back(-X[B][j][i]);
                    }
                }
                --B;
            }
            if (P[t] == 'L') {
                for (int i = U; i <= B; ++i) {
                    for (int j = X[i][L].size() - 1; j >= 0; --j) {
                        X[i][L + 1].push_back(-X[i][L][j]);
                    }
                }
                ++L;
            }
            if (P[t] == 'R') {
                for (int i = U; i <= B; ++i) {
                    for (int j = X[i][R].size() - 1; j >= 0; --j) {
                        X[i][R - 1].push_back(-X[i][R][j]);
                    }
                }
                --R;
            }
        }

        cout << "Case " << times << ":";
        for (int i = 0; i < X[U][L].size(); ++i) {
            if (X[U][L][i] > 0) cout << " " << X[U][L][i];
        }
        cout << endl;
    }
    return 0;
}
