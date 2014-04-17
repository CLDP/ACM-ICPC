#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    int v, t, k, b;
    bool f;
    node() {}
    node(int _v, int _t, int _k, int _b, bool _f) : v(_v), t(_t), k(_k), b(_b), f(_f) {}
};

struct line {
    int v, t, p;
    line() {}
    line(int _v, int _t, int _p) : v(_v), t(_t), p(_p) {}
};


int N, M, B, K, R, T;
int d[101][201][5][5][2];
vector<line> X[110];
int price[6][110];


int main() {
    int TT;
    cin >> TT;
    for (int times = 1; times <= TT; ++times) {
        cin >> N >> M >> B >> K >> R >> T;
        for (int i = 0; i < K; ++i)
         for (int j = 1; j <= N; ++j) cin >> price[i][j];
        for (int i = 1; i <= N; ++i) X[i].clear();
        
        for (int i = 0; i < M; ++i) {
            line S;
            int a;
            cin >> a >> S.v >> S.t >> S.p;
            X[a].push_back(S);
        }
        memset(d, -1, sizeof(d));
        
        d[1][0][0][0][0] = R;
        
        for (int t = 0; t < T; ++t) {
            // buy salt
            for (int i = 2; i < N; ++i)
             for (int j = 0; j < K; ++j) 
              for (int k = 0; k <= B; ++k) {
                  if (d[i][t][j][k][1] == -1) continue;
                  int money = d[i][t][j][k][1];
                  if (money >= price[j][i] && k < B) {
                      if (d[i][t][j][k + 1][0] < money - price[j][i]) {
                          d[i][t][j][k + 1][0] = money - price[j][i];
                      }
                  }
                  if (k > 0) {
                      if (d[i][t][j][k - 1][0] < money + price[j][i]) {
                          d[i][t][j][k - 1][0] = money + price[j][i];
                      }
                  }
              }
            
            // move
            for (int i = 1; i < N; ++i)
             for (int j = 0; j < K; ++j) 
              for (int k = 0; k <= B; ++k)
               for (int l = 0; l < 2; ++l) {
                   int money = d[i][t][j][k][l];
                   if (t + 1 <= T) {
                       if (d[i][t + 1][(j + 1) % K][k][1] < money) {
                           d[i][t + 1][(j + 1) % K][k][1] = money;
                       }
                   }
                   
                   for (int p = 0; p < X[i].size(); ++p) {
                       int a = X[i][p].v;
                       if (j != 0 && (a == 1 || a == N)) continue;
                       if (money < X[i][p].p || t + X[i][p].t > T) continue;
                       if (d[a][t + X[i][p].t][j][k][1] < money - X[i][p].p) {
                           d[a][t + X[i][p].t][j][k][1] = money - X[i][p].p;
                       }
                   }
                   
               }
        }
        
        cout << "Case #" << times << ": ";
        int ans = -1;
        for (int i = 0; i <= T; ++i) 
         for (int j = 0; j <= B; ++j) {
             ans = max(ans, d[N][i][0][j][0]);
             ans = max(ans, d[N][i][0][j][1]);
         }
        
        if (ans == -1) cout << "Forever Alone" << endl; else cout << ans << endl;
    }
    return 0;
}
