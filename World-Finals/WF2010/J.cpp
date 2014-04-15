#include <vector>
#include <queue>
#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[20];
vector<pair<int, int> > X[33000];
vector<int> XX[110][110];

int main() {
    int T, N, M, times = 0;
    while (cin >> T) {
        if (T == 0) break;
        cin >> N >> M;
        for (int i = 0; i < (1 << T); ++i) X[i].clear();
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= M; ++j) XX[i][j].clear();
         
        for (int i = 0; i < T; ++i) cin >> x[i];
        for (int i = 0; i < T; ++i) {
            for (int j = 1; j <= x[i]; ++j) {
                if (x[i] % j != 0) continue;
                if (x[i] / j > M) continue;
                if (j > N) break;
                X[1 << i].push_back(make_pair(j, x[i] / j));
                XX[j][x[i] / j].push_back(1 << i);
            }
        }
        for (int i = 2; i <= T; ++i) {
            vector<int> S(T - i, 0);
            for (int j = 0; j < i; ++j) S.push_back(1);
            do {
                int SS = 0, AREA = 0;
                for (int j = 0; j < T; ++j) {
                    if (!S[j]) continue;
                    SS += 1 << j;
                    AREA += x[j];
                }
                
                set<pair<int, int> > ANS;
                for (int j = 1; j <= N; ++j) {
                    if (AREA % j != 0) continue;
                    int a = j, b = AREA / j;
                    if (b > M) continue;
                    // row line
                    bool ready = false;
                    for (int p = 1; p <= a / 2; ++p) {
                        if (ready) break;
                        for (int k = 0; k < XX[p][b].size(); ++k) {
                            if (ready) break;
                            if ((SS | XX[p][b][k]) != SS) continue;
                            for (int l = 0; l < XX[a - p][b].size(); ++l) {
                                if (ready) break;
                                if ((XX[p][b][k] | XX[a - p][b][l]) != SS) continue;
                                ANS.insert(make_pair(a, b));
                                if (!ready) XX[a][b].push_back(SS);
                                ready = true;
                             }
                         }
                    }
                    // column line
                    for (int q = 1; q <= b / 2; ++q) {
                        if (ready) break;
                        for (int k = 0; k < XX[a][q].size(); ++k) {
                            if (ready) break;
                            if ((SS | XX[a][q][k]) != SS) continue;
                            for (int l = 0; l < XX[a][b - q].size(); ++l) {
                                if (ready) break;
                                if ((XX[a][q][k] | XX[a][b - q][l]) != SS) continue;
                                ANS.insert(make_pair(a, b));
                                if (!ready) XX[a][b].push_back(SS);
                                ready = true;
                            }
                        }
                    }
                }
                
                for (set<pair<int, int> >::iterator iter = ANS.begin(); iter != ANS.end(); ++iter) {
                    X[SS].push_back(*iter);
                }
                
            } while (next_permutation(S.begin(), S.end()));
        }
        cout << "Case " << ++times << ": ";
        if (X[(1 << T) - 1].size() > 0) cout << "Yes" << endl; else cout << "No" << endl;
    }
    return 0;
}
