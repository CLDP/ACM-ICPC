#include <iostream>
#include <cstring>
using namespace std;


int main() {
    int n, mm, m, a, b, nn = 0;
    long long ans;
    bool flag;
    int x[100];
    long long f[100];
    cin >> n >> mm;
    while (n != 0 || mm != 0) {
        ++nn;
        cout << "Case " << nn << ": ";
        m = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            for (int j = 0; j < b; ++ j) x[m+j] = a;
            m += b;
        }
        ans = 0;
        flag = false;
        for (int i = 0; i < m; ++i) {
            if (i != 0 && x[i] == x[i-1]) continue;
            memset(f, 0, sizeof(f));
            f[0] = 1;
            for (int j = 0; j < m; ++j)
             if (i != j)
              for (int k = 60; k >= x[j]; --k) f[k] += f[k-x[j]];
            a = mm - x[i];
            if (a < 0) a = 0;
            for (int j = a; j < mm; ++j) ans += f[j];
            if (flag) cout << " ";
            cout << ans;
            flag = true;
            ans = 0;
        }
        cout << endl;
        cin >> n >> mm;
    }

    return 0;
}
