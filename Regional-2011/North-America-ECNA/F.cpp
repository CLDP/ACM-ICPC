#include <iostream>
#include <cstdio>
using namespace std;


int main() {
    int n, nn = 0, m, a, b, s, t, ans;
    int x[101][101], y[101][101];
    cin >> n;
    while (n != 0) {
        ans = 0;
        ++nn;
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j) {
             scanf("%d", &x[i][j]);
             y[i][j] = x[i][j];
        }

        for (int k = 0; k < n; ++k)
         for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
           if (x[i][k] != 0 && x[k][j] != 0 && i != j)
            if (x[i][k] + x[k][j] < x[i][j] || x[i][j] == 0) x[i][j] = x[i][k] + x[k][j];

        cin >> m >> s;
        t = s;
        b = 0;
        for (int i = 1; i < m; ++i) {
            scanf("%d", &a);
            b += y[t][a];
            if (b > x[s][a]) {
                ++ans;
                b = 0;
                s = a;
            }
            t = a;
        }
        cout << "Case " << nn << ": " << ans << endl;
        cin >> n;
    }

    return 0;
}
