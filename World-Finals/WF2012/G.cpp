#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 410;

struct node {
    int x, y, z, k;
};


int N, M;
vector<node> X;
vector<int> x[MAXN];
vector<vector<int> > B; // Block
vector<int> H;          // Holes in each block
int end_point;          // Block in which end point in
double ans;


int get_block(int a, int b, int h, vector<bool> &z) {
    queue<int> que;
    que.push(a);
    while (!que.empty()) {
        a = que.front();
        que.pop();
        B[b].push_back(a);
        if (a == N) end_point = b;
        z[a] = true;
        H[b] += X[a].k;
        for (int i = 0; i < x[a].size(); ++i) {
            if (X[x[a][i]].z <= h && !z[x[a][i]]) {
                z[x[a][i]] = true;
                que.push(x[a][i]);
            }
        }
    }
    return 0;
}

double dist(int a, int b) {
    return sqrt((X[a].x - X[b].x) * (X[a].x - X[b].x)
              + (X[a].y - X[b].y) * (X[a].y - X[b].y) 
              + (X[a].z - X[b].z) * (X[a].z - X[b].z));
}

int dijkstra() {
    int n = B.size();
    vector<vector<double> > D(n, vector<double>(2, 1e20));
    vector<vector<int> > P(n, vector<int>(2, -1));
    vector<vector<bool> > z(n, vector<bool>(2, false));
    
    D[0][0] = H[0] * 0.5;
    D[0][1] = H[0] * 0.5;
    
    for (int i = 0; i < n * 2; ++i) {
        int a = -1, b = 0;
        double temp = 1e20;
        for (int j = 0; j < n; ++j) 
         for (int k = 0; k < 2; ++k)
          if (!z[j][k] && D[j][k] < temp) {
              temp = D[j][k];
              a = j;
              b = k;
          }
        
        if (a == -1) break;
        z[a][b] = true;
        
        for (int j = 0; j < B[a].size(); ++j) {
            if (X[B[a][j]].k == 0) continue;
            if (j == P[a][b] && X[B[a][j]].k == 1) continue;
            for (int k = 0; k < n; ++k) {
                if (k == a) continue;
                if (z[k][0] && z[k][1]) continue;
                vector<double> DT(B[k].size(), 1e20);
                
                for (int l = 0; l < B[k].size(); ++l) {
                    if (X[B[k][l]].k == 0) continue;
                    DT[l] = min(DT[l], D[a][b] - 1 + dist(B[a][j], B[k][l]) + H[k] * 0.5);
                }
                
                for (int l = 0; l < B[k].size(); ++l) {
                    if (DT[l] < D[k][0] && !z[k][0]) {
                        D[k][1] = D[k][0];
                        P[k][1] = P[k][0];
                        D[k][0] = DT[l];
                        P[k][0] = l;
                    } else 
                    if (DT[l] < D[k][1] && !z[k][1]) {
                        D[k][1] = DT[l];
                        P[k][1] = l;
                    }
                }
            }
        }
    }
    
    if (D[end_point][0] < ans) ans = D[end_point][0];
    
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N >> M) {
        ++times;
        X = vector<node>(N + 1);
        set<int> height;
        for (int i = 1; i <= N; ++i) {
            cin >> X[i].x >> X[i].y >> X[i].z >> X[i].k;
            height.insert(X[i].z);
            x[i].clear();
        }
       
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            x[a].push_back(b);
            x[b].push_back(a);
        }
        
        int minH = max(X[1].z, X[N].z);
        ans = 1e20;
        
        for (set<int>::iterator iter = height.begin(); iter != height.end(); ++iter) {
            if (*iter < minH) continue;
            B.clear();
            H.clear();
            vector<bool> z(N + 1, false);
            for (int i = 1; i <= N; ++i) {
                if (z[i] || X[i].z > *iter) continue;
                B.push_back(vector<int>(0));
                H.push_back(0);
                get_block(i, B.size() - 1, *iter, z);
            }
            
            dijkstra();
        }
        
        cout << "Case " << times << ": ";
        if (ans == 1e20) cout << "impossible" << endl; else printf("%.4lf\n", ans);
    }
    
    return 0;
}
