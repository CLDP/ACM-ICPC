#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, time = 0;
    vector<int> x, y;
    while (cin >> n) {
        if (n == 0) break;
        ++time;
        x.clear();
        y.clear();
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            x.push_back(a);
            y.push_back(b);
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        int p = x[(n - 1) / 2], q = y[(n - 1) / 2];
        cout << "Case " << time << ": (" << p << "," << q << ") ";
        
        int ans = 0;
        for (int i = 0; i < n; ++i) ans += abs(x[i] - p) + abs(y[i] - q);
        cout << ans << endl;
    }

    return 0;
}
