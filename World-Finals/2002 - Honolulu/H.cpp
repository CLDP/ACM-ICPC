#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int x[1001], y[1001], z[1001];

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
            y[i] = x[i];
        }
        sort(y, y + N);
        for (int i = 0; i < N; ++i) z[y[i]] = i;
        
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (i == z[x[i]]) continue;
            
            int temp = 1, total = x[i], minN = x[i];
            while (i != z[x[i]]) {
                swap(x[i], x[z[x[i]]]);
                ++temp;
                minN = min(minN, x[i]);
                total += x[i];
            }
            
            if (total - minN + minN * (temp - 1) < total + temp * y[0] + minN + y[0]) {
                ans += total - minN + minN * (temp - 1);
            } else {
                ans += total + temp * y[0] + minN + y[0];
            }
        }
        
        cout << "Case " << ++times << ": " << ans << endl << endl;
    }

    return 0;
}
