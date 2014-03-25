#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct node {
    int a, b;
    node() {}
    node(int _a, int _b) : a(_a), b(_b) {}
};

vector<int> x[21][21];
int d[21][21];
string g[21][21];
bool z[21][21];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        vector<string> X(N);
        for (int i = 0; i < N; ++i) cin >> X[i];
        
        for (int i = 0; i < N; ++i) 
         for (int j = 0; j < X[i].size(); ++j) {
             x[i][j].clear();
             d[i][j] = INF;
             z[i][j] = false;
             for (int k = 0; k < N; ++k) {
                 if (i == k && j == 0) continue;
                 int l = 0;
                 bool flag = true;
                 while (l < X[k].size() && j + l < X[i].size()) {
                     flag &= (X[k][l] == X[i][j + l]);
                     if (!flag) break;
                     ++l;
                 }
                 if (flag) x[i][j].push_back(k);
             }
         }
         
        d[N][0] = INF;
        
        queue<node> que;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < x[i][0].size(); ++j) {
                int k = x[i][0][j];
                if (X[i].size() > X[k].size()) {
                    que.push(node(i, X[k].size()));
                    z[i][X[k].size()] = true;
                    d[i][X[k].size()] = X[k].size();
                    g[i][X[k].size()] = X[k];
                } else
                if (X[i].size() == X[k].size()) {
                    if (X[i].size() < d[N][0]) {
                        d[N][0] = X[i].size();
                        g[N][0] = X[k];
                    } else
                    if (X[i].size() == d[N][0] && g[N][0] > X[k]) {
                        g[N][0] = X[k];
                    }
                }
            }
        }
        
        while (!que.empty()) {
            node T = que.front();
            que.pop();
            
            for (int i = 0; i < x[T.a][T.b].size(); ++i) {
                int j = x[T.a][T.b][i];
                if (T.b + X[j].size() > X[T.a].size()) {
                    int D = X[T.a].size() - T.b;
                    if (d[j][D] > d[T.a][T.b] + D) {
                        d[j][D] = d[T.a][T.b] + D;
                        g[j][D] = g[T.a][T.b] + X[j].substr(0, D);
                        if (!z[j][D]) {
                            que.push(node(j, D));
                            z[j][D] = true;
                        }
                    } else
                    if (d[j][D] == d[T.a][T.b] + D && g[T.a][T.b] + X[j].substr(D) < g[j][D]) {
                        g[j][D] = g[T.a][T.b] + X[j].substr(0, D);
                        if (!z[j][D]) {
                            que.push(node(j, D));
                            z[j][D] = true;
                        }
                    }
                } else
                if (T.b + X[j].size() < X[T.a].size()) {
                    int D = X[j].size() + T.b;
                    if (d[T.a][D] > d[T.a][T.b] + X[j].size()) {
                        d[T.a][D] = d[T.a][T.b] + X[j].size();
                        g[T.a][D] = g[T.a][T.b] + X[j];
                        if (!z[T.a][D]) {
                            que.push(node(T.a, D));
                            z[T.a][D] = true;
                        }
                    } else 
                    if (d[T.a][D] == d[T.a][T.b] + X[j].size() && g[T.a][D] > g[T.a][T.b] + X[j]) {
                        g[T.a][D] = g[T.a][T.b] + X[j];
                        if (!z[T.a][D]) {
                            que.push(node(T.a, D));
                            z[T.a][D] = true;
                        }
                    } 
                } else {
                    if (d[T.a][T.b] + X[j].size() < d[N][0]) {
                        d[N][0] = d[T.a][T.b] + X[j].size();
                        g[N][0] = g[T.a][T.b] + X[j];
                    } else
                    if (d[T.a][T.b] + X[j].size() == d[N][0] && g[N][0] > g[T.a][T.b] + X[j]) {
                        g[N][0] = g[T.a][T.b] + X[j];
                    }
                }
            }
            
            z[T.a][T.b] = false;
        }
        
        cout << "Code " << ++times << ": " << g[N][0].size() << " bits" << endl; 
        for (int i = 0; i < g[N][0].size(); i += 20) {
            if (i + 20 > g[N][0].size()) {
                cout << g[N][0].substr(i, g[N][0].size() - i) << endl;
            } else {
                cout << g[N][0].substr(i, 20) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
