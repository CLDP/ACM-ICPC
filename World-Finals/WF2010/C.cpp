#include <vector>
#include <queue>
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3010;

struct node {
    int x1, y1, x2, y2;
};

node X[1010];
bool x[MAXN][MAXN];
long long LX[MAXN], LY[MAXN];


int main() {
    int N, M, T, times = 0;
    while (cin >> M >> N >> T) {
        if (N == 0) break;
        map<int, int> CX, CY;
        for (int i = 0; i < T; ++i) {
            cin >> X[i].x1 >> X[i].y1 >> X[i].x2 >> X[i].y2;
            CX[X[i].x1] = CX[X[i].x2 + 1] = 0;
            CY[X[i].y1] = CY[X[i].y2 + 1] = 0;
        }
        CX[0] = CX[N] = 0;
        CY[0] = CY[M] = 0;
        int NN = 0, MM = 0;
        for (map<int, int>::iterator iter = CX.begin(); iter != CX.end(); ++iter) {
            iter->second = NN++;
        }
        for (map<int, int>::iterator iter = CY.begin(); iter != CY.end(); ++iter) {
            iter->second = MM++;
        }
        map<int, int>::iterator iter = CX.begin();
        for (int i = 0; i < NN - 1; ++i) {
            map<int, int>::iterator iter2 = iter;
            ++iter2;
            LX[i] = iter2->first - iter->first;
            iter = iter2;
        }
        iter = CY.begin();
        for (int i = 0; i < MM - 1; ++i) {
            map<int, int>::iterator iter2 = iter;
            ++iter2;
            LY[i] = iter2->first - iter->first;
            iter = iter2;
        }
        memset(x, 0, sizeof(x));
        for (int i = 0; i < T; ++i) {
            int a = CX[X[i].x1], b = CX[X[i].x2 + 1], c = CY[X[i].y1];
            for (int p = a; p < b; ++p) x[p][c] = true;
        }
        
        queue<pair<int, int> > que;
        if (!x[NN - 2][MM - 2]) {
            x[NN - 2][MM - 2] = true;
            que.push(make_pair(NN - 2, MM - 2)); 
        }
        while (!que.empty()) {
            int a  = que.front().first, b = que.front().second;
            que.pop();
            if (a > 0 && !x[a - 1][b]) {
                x[a - 1][b] = true;
                que.push(make_pair(a - 1, b));
            }
            if (b > 0 && !x[a][b - 1]) {
                x[a][b - 1] = true;
                que.push(make_pair(a, b - 1));
            }
        }
        long long ans = 0;
        for (int i = 0; i < NN - 1; ++i)
         for (int j = 0; j < MM - 1; ++j) {
             if (!x[i][j]) ans += LX[i] * LY[j];
         }
        
        cout << "Case " << ++times << ": " << ans << endl;
        
    }
    return 0;
}
