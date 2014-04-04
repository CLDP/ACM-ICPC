#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;

struct state {
    vector<pair<int, int> > X;
    int go;
};


int now[5][5];
bool WALL[5][5][5][5];
map<vector<pair<int, int> >, bool> Z;

int setUp(int N, int M, const state &S, const vector<pair<int, int> > &Y) {
    memset(now, 0, sizeof(now));
    for (int i = 0; i < M; ++i) now[Y[i].first][Y[i].second] = -i - 1;
    for (int i = 0; i < M; ++i) {
        if (S.X[i].first == -1) {
            if (now[Y[i].first][Y[i].second] == - i - 1) now[Y[i].first][Y[i].second] = 0;
            continue;
        }
        now[S.X[i].first][S.X[i].second] = i + 1;
    }
    return 0;
}

int main() {
    int N, M, T, times = 0;
    while (cin >> N >> M >> T) {
        if (N + M + T == 0) break;
        vector<pair<int, int> > X(M), Y(M);
        for (int i = 0; i < M; ++i) cin >> X[i].first >> X[i].second;
        for (int i = 0; i < M; ++i) cin >> Y[i].first >> Y[i].second;
        memset(WALL, 0, sizeof(WALL));
        for (int i = 0; i < T; ++i) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            WALL[a][b][c][d] = WALL[c][d][a][b] = true;
        }
        
        bool output = false;
        
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == j) {
                    if (X[i] == Y[j]) {
                        X[i] = make_pair(-1, -1);
                        continue;
                    }
                }
                if (X[i] == Y[j]) {
                    cout << "Case " << ++times << ": impossible" << endl << endl;
                    output = true;
                    break;
                }
            }
            if (output) break;
        }
        if (output) continue;
        
        
        Z.clear();
        state S;
        S.X = X;
        S.go = 0;
        queue<state> que;
        que.push(S);
        Z[X] = true;
        while (!que.empty()) {
            S = que.front();
            que.pop();
            
            int num = 0;
            for (int i = 0; i < M; ++i) num += (S.X[i].first != -1);
            if (num == 0) {
                output = true;
                cout << "Case " << ++times << ": " << S.go << " moves" << endl << endl;
                break;
            }
            
            state NS;
            
            // X+ go down
            setUp(N, M, S, Y);
            NS = S;
            bool flag = true;
            for (int k = 0; k < N; ++k) {
                for (int i = N - 2; i >= 0; --i) {
                    for (int j = 0; j < N; ++j) {
                        if (now[i][j] <= 0) continue;
                        if (WALL[i][j][i + 1][j]) continue;
                        if (now[i + 1][j] == 0) {
                            NS.X[now[i][j] - 1] = make_pair(i + 1, j); 
                            now[i + 1][j] = now[i][j];
                            now[i][j] = 0;
                            continue;
                        }
                        if (now[i + 1][j] > 0) continue;
                        if (now[i][j] + now[i + 1][j] != 0) {
                            flag = false; 
                            break;
                        } else {
                            NS.X[now[i][j] - 1] = make_pair(-1, -1);
                            now[i][j] = now[i + 1][j] = 0;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            
            if (flag) {
                if (!Z[NS.X]) {
                    Z[NS.X] = true;
                    NS.go = S.go + 1;
                    que.push(NS);
                }
            }
            
            // X- go up
            setUp(N, M, S, Y);
            NS = S;
            flag = true;
            for (int k = 0; k < N; ++k) {
                for (int i = 1; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        if (now[i][j] <= 0) continue;
                        if (WALL[i][j][i - 1][j]) continue;
                        if (now[i - 1][j] == 0) {
                            NS.X[now[i][j] - 1] = make_pair(i - 1, j); 
                            now[i - 1][j] = now[i][j];
                            now[i][j] = 0;
                            continue;
                        }
                        if (now[i - 1][j] > 0) continue;
                        if (now[i][j] + now[i - 1][j] != 0) {
                            flag = false; 
                            break;
                        } else {
                            NS.X[now[i][j] - 1] = make_pair(-1, -1);
                            now[i][j] = now[i - 1][j] = 0;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            
            if (flag) {
                if (!Z[NS.X]) {
                    Z[NS.X] = true;
                    NS.go = S.go + 1;
                    que.push(NS);
                }
            }
            
            
            // Y+ go right
            setUp(N, M, S, Y);
            NS = S;
            flag = true;
            for (int k = 0; k < N; ++k) {
                for (int j = N - 2; j >= 0; --j) {
                    for (int i = 0; i < N; ++i) {
                        if (now[i][j] <= 0) continue;
                        if (WALL[i][j][i][j + 1]) continue;
                        if (now[i][j + 1] == 0) {
                            NS.X[now[i][j] - 1] = make_pair(i, j + 1); 
                            now[i][j + 1] = now[i][j];
                            now[i][j] = 0;
                            continue;
                        }
                        if (now[i][j + 1] > 0) continue;
                        if (now[i][j] + now[i][j + 1] != 0) {
                            flag = false; 
                            break;
                        } else {
                            NS.X[now[i][j] - 1] = make_pair(-1, -1);
                            now[i][j] = now[i][j + 1] = 0;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            
            if (flag) {
                if (!Z[NS.X]) {
                    Z[NS.X] = true;
                    NS.go = S.go + 1;
                    que.push(NS);
                }
            }
            
            
            // Y- go left
            setUp(N, M, S, Y);
            NS = S;
            flag = true;
            for (int k = 0; k < N; ++k) {
                for (int j = 1; j < N; ++j) {
                    for (int i = 0; i < N; ++i) {
                        if (now[i][j] <= 0) continue;
                        if (WALL[i][j][i][j - 1]) continue;
                        if (now[i][j - 1] == 0) {
                            NS.X[now[i][j] - 1] = make_pair(i, j - 1); 
                            now[i][j - 1] = now[i][j];
                            now[i][j] = 0;
                            continue;
                        }
                        if (now[i][j - 1] > 0) continue;
                        if (now[i][j] + now[i][j - 1] != 0) {
                            flag = false; 
                            break;
                        } else {
                            NS.X[now[i][j] - 1] = make_pair(-1, -1);
                            now[i][j] = now[i][j - 1] = 0;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            
            if (flag) {
                if (!Z[NS.X]) {
                    Z[NS.X] = true;
                    NS.go = S.go + 1;
                    que.push(NS);
                }
            }
        }
        
        if (!output) {
            cout << "Case " << ++times << ": impossible" << endl << endl;
        }
    }
    return 0;
}
