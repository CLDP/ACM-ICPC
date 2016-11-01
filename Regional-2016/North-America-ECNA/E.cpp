#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string P;
    cin >> P;
    int ans = P.size();
    for (int i = 0; i < P.size(); ++i) {
        for (int j = 1; j < P.size(); ++j) {
            string Q = P.substr(i, j);
            int k = 0, cnt = 0;
            while (k < P.size()) {
                if (P.substr(k, j) == Q) {
                    k += j;
                } else {
                    ++k;
                }
                ++cnt;
            }
            ans = min(ans, cnt + j);
        }
    }
    cout << ans << endl;
    return 0;
}
