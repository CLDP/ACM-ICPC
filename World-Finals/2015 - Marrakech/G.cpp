#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        double l, v1, v2, t, s;
        cin >> l >> v1 >> v2 >> t >> s;

        bool flag = false;
        double v = v2;
        int n = 1;
        for (int k = 0; ; ++k) {
            if (t * n >= v - v1) {
                cout << k << endl;
                flag = true;
                break;
            }
            double vf = l / s / (k + 1);
            int nf = ceil((v - min(vf + t, v2)) / t);
            n = 2 * (n - nf);
            v = v - nf * t;
            if (n <= 0) break;
        }
        if (!flag) {
            cout << "impossible" << endl;
        }
    }
    return 0;
}
