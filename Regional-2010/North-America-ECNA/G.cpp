#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 10010;

int X[MAXN][MAXN];
vector<string> Va[MAXM];


int main() {
    int v, o, M, times = 0;
    while (cin >> v >> o >> M) {
        ++times;
        if (v == 0 && o == 0 && M == 0) break;
        memset(X, 0, sizeof(X));
        for (int i = 1; i <= v; ++i) {
            int a, b;
            cin >> a >> b;
            X[a][b] = i;
            Va[i].clear();
        }
        for (int i = 0; i < o; ++i) {
            int a, b;
            cin >> a >> b;
            X[a][b] = -1;
        }
        for (int i = 0; i < M; ++i) {
            char C;
            int a, b, c, d;
            cin >> C >> a >> b >> c >> d;
            if (C == 'N') {
                if (a > c) swap(a, c);
                for (int i = a; i <= c; ++i) X[i][b] = -10;
            }
            if (C == 'S') {
                if (a > c) swap(a, c);
                for (int i = a; i <= c; ++i) X[i][b] = -20;
            }
            if (C == 'W') {
                if (b > d) swap(b, d);
                for (int i = b; i <= d; ++i) X[a][i] = -30;
            }
            if (C == 'E') {
                if (b > d) swap(b, d);
                for (int i = b; i <= d; ++i) X[a][i] = -40;
            }
        }

        bool flag = false;
        for (int i = 0; i <= 100; ++i) {
            for (int j = 0; j <= 100; ++j) {
                if (X[i][j] > -2) continue;
                if (X[i][j] == -10) {
                    int b = j;
                    while (b < 100) {
                        ++b;
                        if (X[i][b] == 0) continue;
                        if (X[i][b] < 0) break;
                        Va[X[i][b]].push_back("south");
                        flag = true;
                    }
                }
                if (X[i][j] == -20) {
                    int b = j;
                    while (b > 0) {
                        --b;
                        if (X[i][b] == 0) continue;
                        if (X[i][b] < 0) break;
                        Va[X[i][b]].push_back("north");
                        flag = true;
                    }
                }
                if (X[i][j] == -30) {
                    int a = i;
                    while (a > 0) {
                        --a;
                        if (X[a][j] == 0) continue;
                        if (X[a][j] < 0) break;
                        Va[X[a][j]].push_back("east");
                        flag = true;
                    }
                }
                if (X[i][j] == -40) {
                    int a = i;
                    while (a < 100) {
                        ++a;
                        if (X[a][j] == 0) continue;
                        if (X[a][j] < 0) break;
                        Va[X[a][j]].push_back("west");
                        flag = true;
                    }
                }
            }
        }
        cout << "Case " << times << ":" << endl;
        if (!flag) {
            cout << "none" << endl;
        } else {
            for (int i = 1; i <= v; ++i) {
                if (Va[i].size() == 0) continue;
                cout << "vampire " << i;
                sort(Va[i].begin(), Va[i].end());
                for (int j = 0; j < Va[i].size(); ++j) cout << " " << Va[i][j];
                cout << endl;
            }
        }
    }
    return 0;
}
