#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1010;

int v[MAXN], u[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    while (N--) {
        char p;
        cin >> p;
        string Q;
        getline(cin, Q);
        Q = Q.substr(1, Q.size());

        if (p == 'e') {
            for (int i = 0; i < Q.size(); ++i) {
                if (Q[i] == ' ') v[i] = 0; else v[i] = Q[i] - 'a' + 1;
            }
            u[0] = v[0];
            for (int i = 1; i < Q.size(); ++i) {
                u[i] = (u[i - 1] + v[i]) % 27;
            }
            for (int i = 0; i < Q.size(); ++i) {
                if (u[i] == 0) cout << " "; else cout << (char)('a' - 1 + u[i]);
            }

            cout << endl;
        } else {
            for (int i = 0; i < Q.size(); ++i) {
                if (Q[i] == ' ') u[i] = 0; else u[i] = Q[i] - 'a' + 1;
            }
            v[0] = u[0];
            for (int i = 1; i < Q.size(); ++i) {
                v[i] = (u[i] - u[i - 1] + 2700) % 27;
            }
            for (int i = 0; i < Q.size(); ++i) {
                if (v[i] == 0) cout << " "; else cout << (char)('a' - 1 + v[i]);
            }
            cout << endl;
        }
    }

    return 0;
}
