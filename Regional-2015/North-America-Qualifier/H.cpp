#include <iostream>
#include <cstring>
using namespace std;

char x[101][101];

int main() {
    int N;
    cin >> N;
    for (int t = 0; t < N; ++t) {
        string Q;
        cin >> Q;
        int M = 1;
        while (M * M < Q.size()) ++M;
        memset(x, 0, sizeof(x));
        for (int i = 0; i < Q.size(); ++i) x[i / M][i % M] = Q[i];
        for (int j = 0; j < M; ++j) {
            for (int i = M - 1; i >= 0; --i) {
                if (x[i][j] == 0) continue;
                cout << x[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}
