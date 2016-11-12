#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

// 0 for w, 1 for e
int f[252][252][252][2];

struct car {
    int a, r;
};

int main() {
    memset(f, -1, sizeof(f));
    int t, n;
    
    cin >> t >> n;
    vector<car> w, e;
    
    for (int i = 0; i < n; ++i) {
        char c;
        car tc;
        cin >> c >> tc.a >> tc.r;
        if (c == 'W')
            w.push_back(tc);
        else
            e.push_back(tc);
    }
    
    if (w.size() > 0) f[1][0][0][0] = w[0].a;
    if (e.size() > 0) f[0][1][0][1] = e[0].a;
    
    for (int i = 0; i <= w.size(); ++i)
        for (int j = 0; j <= e.size(); ++j) {
            if ((i + j == 0) || (i + j == n)) continue;
            for (int k = 0; k < i + j; ++k) {
                if (f[i][j][k][0] >= 0) {
                    if (i < w.size()) {
                        int tmp = max(f[i][j][k][0] + 3, w[i].a);
                        if (tmp <= w[i].a + w[i].r)
                            f[i+1][j][k][0] = (f[i+1][j][k][0] == -1) ? tmp : min(f[i+1][j][k][0], tmp);
                        else
                            f[i+1][j][k+1][0] = (f[i+1][j][k+1][0] == -1) ? tmp : min(f[i+1][j][k+1][0], tmp);
                    }
                    if (j < e.size()) {
                        int tmp = max(f[i][j][k][0] + t, e[j].a);
                        if (tmp <= e[j].a + e[j].r)
                            f[i][j+1][k][1] = (f[i][j+1][k][1] == -1) ? tmp : min(f[i][j+1][k][1], tmp);
                        else
                            f[i][j+1][k+1][1] = (f[i][j+1][k+1][1] == -1) ? tmp : min(f[i][j+1][k+1][1], tmp);
                    }
                }
                if (f[i][j][k][1] >= 0) {
                    if (i < w.size()) {
                        int tmp = max(f[i][j][k][1] + t, w[i].a);
                        if (tmp <= w[i].a + w[i].r)
                            f[i+1][j][k][0] = (f[i+1][j][k][0] == -1) ? tmp : min(f[i+1][j][k][0], tmp);
                        else
                            f[i+1][j][k+1][0] = (f[i+1][j][k+1][0] == -1) ? tmp : min(f[i+1][j][k+1][0], tmp);
                    }
                    if (j < e.size()) {
                        int tmp = max(f[i][j][k][1] + 3, e[j].a);
                        if (tmp <= e[j].a + e[j].r)
                            f[i][j+1][k][1] = (f[i][j+1][k][1] == -1) ? tmp : min(f[i][j+1][k][1], tmp);
                        else
                            f[i][j+1][k+1][1] = (f[i][j+1][k+1][1] == -1) ? tmp : min(f[i][j+1][k+1][1], tmp);
                    }
                }
            }
        }
    
    int res = n;
    for (int i = n; i >= 0; --i)
        if ((f[w.size()][e.size()][i][0] >= 0) || (f[w.size()][e.size()][i][1] >= 0)) res = i;

    cout << res << endl;

    return 0;
}
