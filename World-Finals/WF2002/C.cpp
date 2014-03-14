#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000;

int N;
double M;
double x[21], y[21];
double dist[21][21];
double d[21];
bool z[21];


bool check(int mid) {
    for (int i = 0; i < N; ++i) {
        d[i] = -1;
        z[i] = false;
    }
    
    queue<int> que;
    z[0] = true;
    que.push(0);
    d[0] = mid;
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        if (a == N - 1) return true;
        for (int i = 0; i < N; ++i) {
            if (i == a) continue;
            if (dist[a][i] > M / 2) continue;
            if (dist[a][i] > d[a]) continue;
            double PA = d[a], NC;
            if (dist[a][i] < M / 3) {
                // can be back
                int times = d[a] / (M - dist[a][i]);
                double NA = times * (M - 3 * dist[a][i]);
                PA -= times * (M - dist[a][i]);
                double NB = 0;
                if (dist[a][i] < PA) NB = PA - dist[a][i];
                NC = NA + NB;
                if (times > 0) NC = max(NC, NA + dist[a][i]);
            } else {
                NC = min(M - 2 * dist[a][i], d[a] - dist[a][i]);
            }
            if (NC > d[i]) {
                d[i] = NC;
                if (!z[i]) {
                    z[i] = true;
                    que.push(i);
                }
            }
        }
        z[a] = false;
    }
    return false;
}


int main() {
    int times = 0;
    while (++times) {
        cin >> N >> M;
        if (N == 0 && M == 0) break;
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) 
          dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        if (!check(INF)) {
            cout << "Trial " << times << ": Impossible" << endl << endl;
            continue;
        }
        int L = 0, R = INF;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            if (check(mid)) R = mid; else L = mid;
        }
        cout << "Trial " << times << ": " << R << " units of food" << endl;
        cout << endl;
    }
    return 0;
}
