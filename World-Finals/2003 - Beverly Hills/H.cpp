#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXT = 1010;
const int MAXN = 101;
const int INF = 1000000000;


int dd[MAXN], ds[MAXN], dt[MAXN];
int d[MAXT][MAXN];
bool z[MAXT][MAXN];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        int T;
        cin >> T;
        for (int i = 1; i < N; ++i) cin >> dd[i];
        ds[0] = 0;
        for (int i = 1; i < N; ++i) ds[i] = ds[i - 1] + dd[i];
        dt[N - 1] = 0;
        for (int i = N - 2; i >= 0; --i) dt[i] = dt[i + 1] + dd[i + 1];
        
        int M1, M2;
        cin >> M1;
        vector<int> TS(M1);
        for (int i = 0; i < M1; ++i) cin >> TS[i];
        cin >> M2;
        vector<int> TT(M2);
        for (int i = 0; i < M2; ++i) cin >> TT[i];
        for (int i = 0; i <= T; ++i)
         for (int j = 0; j < N; ++j) d[i][j] = INF;
       
        memset(z, 0, sizeof(z));
        d[0][0] = 0;
        z[0][0] = true;
        queue<pair<int, int> > que;
        que.push(make_pair(0, 0));
        while (!que.empty()) {
            int a = que.front().first, b = que.front().second;
            que.pop();
            //a == time b == station
            if (b < N - 1) {
                for (int i = 0; i < M1; ++i) {
                    if (TS[i] + ds[b] < a) continue;
                    int wait = TS[i] + ds[b] - a;
                    int aa = a + wait + ds[b + 1] - ds[b], bb = b + 1;
                    if (d[aa][bb] > d[a][b] + wait) {
                        d[aa][bb] = d[a][b] + wait;
                        if (!z[aa][bb]) {
                            z[aa][bb] = true;
                            que.push(make_pair(aa, bb));
                        }
                    }
                }
            }
            if (b > 0) {
                for (int i = 0; i < M2; ++i) {
                    if (TT[i] + dt[b] < a) continue;
                    int wait = TT[i] + dt[b] - a;
                    int aa = a + wait + dt[b - 1] - dt[b], bb = b - 1;
                    if (d[aa][bb] > d[a][b] + wait) {
                        d[aa][bb] = d[a][b] + wait;
                        if (!z[aa][bb]) {
                            z[aa][bb] = true;
                            que.push(make_pair(aa, bb));
                        }
                    }
                }
            }
            
            z[a][b] = false;
        }
        
        int ans = INF;
        for (int i = 0; i <= T; ++i) ans = min(ans, d[i][N - 1] + T - i);
        cout << "Case Number " << ++times << ": ";
        if (ans > T) {
            cout << "impossible" << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}
