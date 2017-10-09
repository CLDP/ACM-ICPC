#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1010;

const int MX[4] = {0, 1, 0, -1};
const int MY[4] = {1, 0, -1, 0};

int x[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int a, b, N;
    cin >> a >> b >> N;
    for (int i = 0; i < N; ++i) {
        string P;
        cin >> P;
        if (P[0] == 'F') x[i] = 0; 
        if (P[0] == 'L') x[i] = 1;
        if (P[0] == 'R') x[i] = 2;
    }


    for (int i = 0; i < N; ++i) {
        int temp = x[i];
        for (int j = 0; j < 3; ++j) {
            x[i] = j;

            int p = 0, q = 0, r = 0;
            for (int k = 0; k < N; ++k) {
                if (x[k] == 0) {
                    p += MX[r];
                    q += MY[r];
                } else
                if (x[k] == 1) {
                    r = (r + 3) % 4;
                } else {
                    r = (r + 1) % 4;
                }
            }
            if (p == a && q == b) {
                cout << i + 1 << " ";
                if (j == 0) cout << "Forward" << endl;
                if (j == 1) cout << "Left" << endl;
                if (j == 2) cout << "Right" << endl;
                return 0;
            }
        }
        x[i] = temp;
    }

    return 0;
}
