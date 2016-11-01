#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    string P, Q, R;
    cin >> P >> Q;
    int j = 0, k = 0;
    for (int i = 0; i < P.size(); ++i) {
        char C;
        if (j < Q.size()) {
            C = Q[j];
            ++j;
        } else {
            C = R[k];
            ++k;
        }
        C = P[i] - (C - 'A');
        if (C < 'A') C += 26;
        R = R + C;
    }
    cout << R << endl;
    return 0;
}
