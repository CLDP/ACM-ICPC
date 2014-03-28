#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int d[52];
bool z[52];
vector<int> x[52];

int change(string P) {
    if (P[0] >= 'A' && P[0] <= 'Z') return P[0] - 'A'; else return P[0] - 'a' + 26;
}

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == -1) break;
        for (int i = 0; i < 52; ++i) x[i].clear();
        string P, Q;
        for (int i = 0; i < N; ++i) {
            cin >> P >> Q;
            int a = change(P), b = change(Q);
            x[a].push_back(b);
            x[b].push_back(a);
        }
        int M;
        cin >> M >> P >> Q;
        int s = change(P), t = change(Q);
        
        for (int i = 0; i < 52; ++i) {
            d[i] = INF;
            z[i] = false;
        }
        queue<int> que;
        que.push(t);
        d[t] = M;
        z[t] = true;
        while (!que.empty()) {
            int a = que.front(), b;
            que.pop();
            if (a < 26) {
                b = d[a] + 1 + d[a] / 19;
                while (b - 1 - (b + 18) / 20 >= d[a]) --b;
            } else {
                b = d[a] + 1;
            }
            for (int i = 0; i < x[a].size(); ++i) {
                if (d[x[a][i]] > b) {
                    d[x[a][i]] = b;
                    if (!z[x[a][i]]) {
                        z[x[a][i]] = true;
                        que.push(x[a][i]);
                    }
                }
            }
            z[a] = false;
        }
        
        cout << "Case " << ++times << ": " << d[s] << endl;
    }

    return 0;
}
