#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;

struct Point {
    int x, y;
};

Point X[MAXN];
double f[MAXN][MAXN];
int lx[MAXN][MAXN], ly[MAXN][MAXN];

double dis(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int update(int x1, int y1, int x2, int y2, double dis) {
    if (f[x1][y1] + dis < f[x2][y2]) {
        f[x2][y2] = f[x1][y1] + dis;
        lx[x2][y2] = x1;
        ly[x2][y2] = y1;
    }
    return 0;
}


int main() {
    int times = 0, N, P, Q;
    while (cin >> N >> P >> Q) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> X[i].x >> X[i].y;
        
        for (int i = 0; i < N; ++i) 
         for (int j = 0; j < N; ++j) f[i][j] = 1e10;
        
        f[0][0] = 0;
        
        for (int k = 1; k < N; ++k) {
            if (Q != k) {
                for (int i = 0; i < k; ++i) {
                    update(k - 1, i, k, i, dis(X[k - 1], X[k]));
                    update(i, k - 1, k, k - 1, dis(X[i], X[k]));
                }
            }
            if (P != k) {
                for (int i = 0; i < k; ++i) {
                    update(i, k - 1, i, k, dis(X[k - 1], X[k]));
                    update(k - 1, i, k - 1, k, dis(X[i], X[k]));
                }
            }
        }
        double ans = 1e10;
        int p, q;
        for (int i = 0; i < N; ++i) {
            if (f[i][N - 1] + dis(X[i], X[N - 1]) < ans) {
                ans = f[i][N - 1] + dis(X[i], X[N - 1]);
                p = i, q = N - 1;
            } else 
            if (f[N - 1][i] + dis(X[i], X[N - 1]) < ans) {
                ans = f[N - 1][i] + dis(X[i], X[N - 1]);
                p = N - 1, q = i;
            }
        }
        vector<int> L, R;
        L.push_back(p);
        R.push_back(q);
        while (p != 0 || q != 0) {
            int r = lx[p][q], s = ly[p][q];
            p = r, q = s;
            L.push_back(p);
            R.push_back(q);
        }
        
        printf("Case %d: %.2lf\n", ++times, ans);
        vector<int> ansT;
        for (int i = L.size() - 1; i >= 0; --i)
         if (i == L.size() - 1 || L[i] != L[i + 1]) ansT.push_back(L[i]);
        for (int i = 0; i < R.size(); ++i)
         if (i == 0 || R[i] != R[i - 1]) ansT.push_back(R[i]);
        
        if (ansT[1] != 1) {
            int NN = ansT.size();
            for (int i = 0; i < NN / 2; ++i) swap(ansT[i], ansT[NN - 1 - i]);
        }
        for (int i = 0; i < ansT.size(); ++i) {
            cout << ansT[i];
            if (i == ansT.size() - 1) cout << endl; else cout << " ";
        }
    }
    return 0;
}
