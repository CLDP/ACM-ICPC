#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct box {
    int a, b, c;
};

int f[(1 << 10) - 1][10][3];
int ans;
int n;
vector<box> all;

int dp(int a, int b, int c) {
    if (f[a][b][c] > 0) return f[a][b][c];
    f[a][b][c] = 1;
    for (int i = 0; i < n; ++i)
        if (((1 << i) & a) == 0) {
            if (c == 0) {
                if (all[i].b <= all[b].b && all[i].c <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 0) + 1);
                }
                if (all[i].a <= all[b].b && all[i].c <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 1) + 1);
                }
                if (all[i].a <= all[b].b && all[i].b <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 2) + 1);
                }
            } else
            if (c == 1) {
                if (all[i].b <= all[b].a && all[i].c <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 0) + 1);
                }
                if (all[i].a <= all[b].a && all[i].c <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 1) + 1);
                }
                if (all[i].a <= all[b].a && all[i].b <= all[b].c) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 2) + 1);
                }
            } else {
                if (all[i].b <= all[b].a && all[i].c <= all[b].b) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 0) + 1);
                }
                if (all[i].a <= all[b].a && all[i].c <= all[b].b) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 1) + 1);
                }
                if (all[i].a <= all[b].a && all[i].b <= all[b].b) {
                    f[a][b][c] = max(f[a][b][c], dp((1 << i) | a, i, 2) + 1);
                }            
            }
        }
    
    if (f[a][b][c] > ans) ans = f[a][b][c];
    return f[a][b][c];
}


int main() {
    int time = 0;
    while (cin >> n) {
        ++time;
        if (n == 0) break;
        memset(f, 0, sizeof(f));
        ans = 0;
        all.clear();
        for (int i = 0; i < n; ++i) {
            box p;
            cin >> p.a >> p.b >> p.c;
            if (p.a > p.b) swap(p.a, p.b);
            if (p.b > p.c) swap(p.b, p.c);
            if (p.a > p.b) swap(p.a, p.b);
            all.push_back(p);
        }
        
        for (int i = 0; i < n; ++i) {
            dp(1 << i, i, 0);
            dp(1 << i, i, 1);
            dp(1 << i, i, 2);
        }
        
        cout << "Case " << time << ": " << ans << endl;
    }
    return 0;
}
