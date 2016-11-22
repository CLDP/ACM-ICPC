#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;
const string ANS[4] = {"A", "B", "AB", "O"};


int change(string P) {
    if (P.size() == 3) return 2;
    if (P[0] == 'A') return 0;
    if (P[0] == 'B') return 1;
    if (P[0] == 'O') return 3;
}

bool check(int a, int b, int c) {
    if (a > b) swap(a, b);
    if (a == 0 && b == 0) return c == 0 || c == 3;
    if (a == 0 && b == 1) return true;
    if (a == 0 && b == 2) return c == 0 || c == 1 || c == 2;
    if (a == 0 && b == 3) return c == 0 || c == 3;
    if (a == 1 && b == 1) return c == 1 || c == 3;
    if (a == 1 && b == 2) return c == 0 || c == 1 || c == 2;
    if (a == 1 && b == 3) return c == 1 || c == 3;
    if (a == 2 && b == 2) return c == 0 || c == 1 || c == 2;
    if (a == 2 && b == 3) return c == 0 || c == 1;
    if (a == 3 && b == 3) return c == 3;
    return false;
}

int print(vector<string> &ans) {
    if (ans.size() == 0) {
        cout << "IMPOSSIBLE";
    } else
    if (ans.size() == 1) {
        cout << ans[0];
    } else {
        cout << "{";
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i];
            if (i != ans.size() - 1) cout << ", "; else cout << "}";
        }
    }
    return 0;
}

int main() {
    int times = 0;
    string P, Q, R;
    while (cin >> P >> Q >> R) {
        if (P == "E") break;
        bool flag = false;
        if (Q == "?") {
            swap(P, Q);
            flag = true;
        }
        vector<string> ans;
        if (P == "?") {
            int b, c;
            b = change(Q);
            c = change(R);
            vector<string> sign;
            if (Q[Q.size() - 1] == '+') {
                sign.push_back("+");
                sign.push_back("-");
            } else
            if (R[R.size() - 1] == '+') {
                sign.push_back("+");
            } else {
                sign.push_back("+");
                sign.push_back("-");
            }
            for (int i = 0; i < 4; ++i) {
                if (check(i, b, c)) {
                    for (int j = 0; j < sign.size(); ++j) ans.push_back(ANS[i] + sign[j]);
                }
            }
            cout << "Case " << ++times << ": ";
            if (!flag) {
                print(ans);
                cout << " " << Q << " " << R << endl;
            } else {
                cout << Q << " ";
                print(ans);
                cout << " " << R << endl;
            }
        } else {
            int a, b;
            a = change(P);
            b = change(Q);
            vector<string> sign;
            if (P[P.size() - 1] == '-' && Q[Q.size() - 1] == '-') {
                sign.push_back("-");
            } else {
                sign.push_back("+");
                sign.push_back("-");
            }
            for (int i = 0; i < 4; ++i) {
                if (check(a, b, i)) {
                    for (int j = 0; j < sign.size(); ++j) ans.push_back(ANS[i] + sign[j]);
                }
            }
            cout << "Case " << ++times << ": " << P << " " << Q << " ";
            print(ans);
            cout << endl;
        }
    }
    return 0;
}
