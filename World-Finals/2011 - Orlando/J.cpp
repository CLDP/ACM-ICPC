#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 1000010;
const int INF = 1000000000;

int high[1100], low[1100];
int f[MAXN];
vector<int> g[MAXN];

int main() {
    high[1] = low[1] = 1;
    for (int i = 2; i < 200; ++i) {
        int temp = i * i;
        high[i] = high[i - 1] + temp;
        low[i] = low[i - 2] + i * i;
    }
    
    for (int i = 1; i < MAXN; ++i) f[i] = INF;
    
    for (int i = 2, j = 3; high[i] < MAXN || low[j] < MAXN; ) {
        if (high[i] < low[j]) {
            for (int k = 1000000; k >= high[i]; --k) {
                if (f[k - high[i]] + 1 <= f[k]) {
                    f[k] = f[k - high[i]] + 1;
                    g[k] = g[k - high[i]];
                    g[k].push_back(i);
                }
            }
            ++i;
        } else {
            for (int k = 1000000; k >= low[j]; --k) {
                if (f[k - low[j]] + 1 <= f[k]) {
                    f[k] = f[k - low[j]] + 1;
                    g[k] = g[k - low[j]];
                    g[k].push_back(-j);
                }
            }
            ++j;
        }
    }
    
    
    int M, times = 0;
    while (cin >> M) {
        if (M == 0) break;
        cout << "Case " << ++times << ":";
        if (f[M] == INF) {
            cout << " impossible" << endl;
            continue;
        }
        int T = g[M].size();
        while (T > 0) {
            --T;
            if (g[M][T] > 0) cout << " " << g[M][T] << "H"; else cout << " " << -g[M][T] << "L";
        }
        cout << endl;
    }
    
    
    return 0;
}
