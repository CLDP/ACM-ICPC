#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b, nn = 0, ans, c, d;
    cin >> a >> b;
    while (a != 0 || b != 0) {
        ++nn;
        ans = 0;
        c = sqrt(2*(a-1));
        while (c*(c+1)/2+1 < b) {
            d = c*(c+1)/2+1;
            if (d <= a) {
                ++c;
                continue;
            }
            int e = sqrt(d);
            if (e*e == d) ++ans;
            ++c;
        }

        cout << "Case " << nn << ": " << ans << endl;
        cin >> a >> b;
    }

    return 0;
}
