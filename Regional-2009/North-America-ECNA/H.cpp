#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 110;
int x[MAXN], y[MAXN], xa[MAXN], ya[MAXN];


int main() {
    int tt = 0, n, m, a, b;
    bool flag = false;
    cin >> n;
    while (n) {
        ++tt;
        cout << "Desktop " << tt << ":" << endl;
        for (int i = 0; i < n; ++i) cin >> x[i] >> y[i] >> ya[i] >> xa[i];
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b;
            flag = false;
            for (int j = n-1; j >= 0; --j) {
                if (x[j] <= a && y[j] <= b && x[j]+xa[j] > a && y[j]+ya[j] > b) {
                    cout << "window " << j+1 << endl;
                    flag = true;
                    break;
                }
            }
            if (!flag) cout << "background" << endl;
        }
        cin >> n;
    }

    return 0;
}
