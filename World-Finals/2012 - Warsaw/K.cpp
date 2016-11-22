#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 51;
const int MAXH = 10001;
const int INF = 1000000000;

int N;
vector<int> x[MAXH];
int s[MAXN], sn[MAXH];
bool z[MAXN][MAXH];
int f[MAXH][MAXN];
int cz[MAXH][MAXN];

int DP(int a, int b) {
    if (cz[a][b]) return f[a][b];
    cz[a][b] = true;
    if (a == 0) return 0;
    f[a][b] = INF;
    int c = a - 1;
    while (x[c].size() == 0 && c > 0) --c;
    for (int i = 0; i < N; ++i) {
        if (!z[i][c]) continue;
        int temp = DP(c, i) + x[a].size() - 1 + !z[i][a];
        // Welcome back
        if (x[a].size() > 1 && i == b) ++temp;
        if (temp < f[a][b]) f[a][b] = temp;
    }
    return f[a][b];
}


int main() {
    int times = 0;
    while (cin >> N) {
        ++times;
        for (int i = 0; i < MAXH; ++i) x[i].clear();
        memset(z, 0, sizeof(z));
        memset(f, 0, sizeof(f));
        memset(sn, 0, sizeof(sn));
        memset(cz, 0, sizeof(cz));
        int H = 0;
        for (int i = 0; i < N; ++i) {
            z[i][0] = true;
            int M;
            cin >> M;
            s[i] = MAXH;
            for (int j = 0; j < M; ++j) {
                int a;
                cin >> a;
                H = max(H, a);
                s[i] = min(s[i], a);
                if (x[a].empty() || x[a][x[a].size() - 1] != i) x[a].push_back(i);
                z[i][a] = true;
            }
            ++sn[s[i]];
        }
        
        int ans = INF;
        for (int i = 0; i < N; ++i) 
         if (z[i][H]) ans = min(ans, DP(H, i) + 1 - N);
        cout << "Case " << times << ": " << ans + ans + N - 1 << endl;
    }
    return 0;
}
