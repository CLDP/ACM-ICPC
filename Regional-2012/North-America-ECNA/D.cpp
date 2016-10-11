#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool check(vector<int> &X, vector<int> &Y) {
    for (int i = 0; i < 6; ++i)
     if (X[i] != Y[i]) return false;
    return true;
}

int update(vector<int> &Y) {
    int i = 0;
    while (Y[i] == 0) ++i;
    ++Y[i + 1];
    Y[0] = Y[i] - 1;
    if (i != 0) Y[i] = 0;
    return 0;
}

int main() {
    char C;
    int times = 0;
    while (cin >> C) {
        if (C == 'e') break;
        ++times;
        cout << "Case " << times << ":";

        int T;
        vector<int> X(6, 0), Y(6, 0);
        if (C == 'm') {
            for (int i = 0; i < 6; ++i) cin >> X[5 - i];
            Y[0] = 15;
            T = 0;
            while (!check(X, Y)) {
                ++T;
                update(Y);
            }
            cout << " " << T << endl;
        } else {
            cin >> T;
            Y[0] = 15;
            while (T--) {
                update(Y);
            }
            for (int i = 0; i < 6; ++i) cout << " " << Y[5 - i];
            cout << endl;
        }
    }
    return 0;
}
