#include <iostream>
#include <string>
using namespace std;

const int MAXN = 26;

bool x[MAXN][MAXN];

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        char a, b;
        cin >> a >> b;
        x[a - 'a'][b - 'a'] = true;
    }
    for (int i = 0; i < 26; ++i) x[i][i] = true;

    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                x[i][j] |= (x[i][k] & x[k][j]);
            }
        }
    }
    for (int i = 0; i < M; ++i) {
        string P, Q;
        cin >> P >> Q;
        bool flag = true;
        if (P.size() != Q.size()) flag = false;
        for (int j = 0; j < P.size(); ++j) flag &= x[P[j] - 'a'][Q[j] - 'a'];
        if (flag) cout << "yes" << endl; else cout << "no" << endl;
    }

    return 0;
}
