#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

const int MAXN = 3100;
const int INF = 1000000000;
const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};

struct SEG {
    int x1, y1, x2, y2;
};

bool w[MAXN][MAXN], z[MAXN][MAXN];
int d[MAXN][MAXN];

int main() {
    int times = 0, N;
    while (cin >> N) {
        if (N == 0) break;
        vector<SEG> X(N);
        map<int, int> xx, yy;
        for (int i = 0; i < N; ++i) {
            cin >> X[i].x1 >> X[i].y1 >> X[i].x2 >> X[i].y2;
            if (X[i].x1 > X[i].x2) swap(X[i].x1, X[i].x2);
            if (X[i].y1 > X[i].y2) swap(X[i].y1, X[i].y2);
            xx[X[i].x1] = xx[X[i].x2] = yy[X[i].y1] = yy[X[i].y2] = 0;
        }
        SEG R;
        cin >> R.x1 >> R.y1 >> R.x2 >> R.y2;
        xx[R.x1] = xx[R.x2] = yy[R.y1] = yy[R.y2] = 0;
        
        int XS = 0, YS = 0;
        for (map<int, int>::iterator iter = xx.begin(); iter != xx.end(); ++iter) {
            iter->second = XS;
            XS += 2;
        }
        for (map<int, int>::iterator iter = yy.begin(); iter != yy.end(); ++iter) {
            iter->second = YS;
            YS += 2;
        }
        
        memset(w, 0, sizeof(w));
        for (int i = 0; i < XS; ++i)
         for (int j = 0; j < YS; ++j) d[i][j] = INF;
        
        for (int i = 0; i < N; ++i) {
            if (X[i].x1 == X[i].x2) {
                int xa = xx[X[i].x1], ys = yy[X[i].y1], yt = yy[X[i].y2];
                for (int j = ys; j <= yt; ++j) w[xa][j] = true;
            } else {
                int ya = yy[X[i].y1], xs = xx[X[i].x1], xt = xx[X[i].x2];
                for (int j = xs; j <= xt; ++j) w[j][ya] = true;
            }
        }
        
        int xs = xx[R.x1], ys = yy[R.y1], xt = xx[R.x2], yt = yy[R.y2];
        queue<pair<int, int> > que;
        z[xs][ys] = true;
        d[xs][ys] = 0;
        que.push(make_pair(xs, ys));
        while (!que.empty()) {
            int a = que.front().first, b = que.front().second;
            que.pop();
            for (int i = 0; i < 4; ++i) {
                int p = a + MX[i], q = b + MY[i];
                if (p >= 0 && p < XS && q >= 0 && q < YS) {
                    if (d[p][q] > d[a][b] + w[p][q]) {
                        d[p][q] = d[a][b] + w[p][q];
                        if (!z[p][q]) {
                            z[p][q] = true;
                            que.push(make_pair(p, q));
                        }
                    }
                }
            }
            z[a][b] = false;
        }
        cout << "City " << ++times << endl;
        cout << "Peter has to cross " << d[xt][yt] << " streets" << endl;
    }
    
    return 0;
}
