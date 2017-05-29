#include <iostream>
#include <vector>
using namespace std;

const int ANY = 100;
const int NONE = -1;
const int NOANS = -100;

int N;
int x;
int y[55][5];
bool cz[1 << 21];

vector<int> X2, X3, X4;

bool correct(int question, int state, int answer) {
    if (answer == NOANS) return true;
    int temp = question & state;
    if (temp > 0) {
        if (answer == ANY) return true;
        if (answer == NONE) return false;
        if ((1 << answer) & temp) return true;
        return false;
    }
    if (answer == NONE) return true;
    return false;
}


bool check(int state, int person) {
    for (int i = 0; i < N; ++i) {
        if (i % 4 == person) continue;
        switch (i % 4) {
            case 0 : if (!correct(y[i][0], state, y[i][person])) return false; break;
            case 1 : if (!correct(y[i][0], state, y[i][(person + 3) % 4])) return false; break;
            case 2 : if (!correct(y[i][0], state, y[i][(person + 2) % 4])) return false; break;
            case 3 : if (!correct(y[i][0], state, y[i][(person + 1) % 4])) return false; break;
        }
    }
    return true;
}

void dfs(vector<int> &X, int a, int p, int state, int person) {
    if (a == 0) {
        if (check(state, person)) X.push_back(state);
        return ;
    }
    for (int i = p; i < 21; ++i) {
        if (x & (1 << i)) continue;
        dfs(X, a - 1, i + 1, state | (1 << i), person);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < 5; ++i) {
        char C;
        cin >> C;
        x |= (1 << (C - 'A'));
    }

    for (int i = 0; i < N; ++i) {
        char C;
        for (int j = 0; j < 3; ++j) {
            cin >> C;
            y[i][0] |= (1 << (C - 'A'));
        }
        for (int j = 1; j < 4; ++j) y[i][j] = NOANS;
        for (int j = 1; j < 4; ++j) {
            cin >> C;
            if (C == '-') {
                y[i][j] = NONE;
            } else 
            if (C == '*') {
                y[i][j] = ANY;
                break;
            } else {
                y[i][j] = C - 'A';
                break;
            }
        }
    }

    dfs(X2, 5, 0, 0, 1);
    dfs(X3, 4, 0, 0, 2);
    dfs(X4, 4, 0, 0, 3);
    int ans = (1 << 21) - 1;
    for (int i = 0; i < X4.size(); ++i) cz[X4[i]] = true;
    for (int i = 0; i < 6; ++i) {
        if (x & (1 << i)) continue;
        for (int j = 6; j < 12; ++j) {
            if (x & (1 << j)) continue;
            for (int k = 12; k < 21; ++k) {
                if (x & (1 << k)) continue;
                int state = (1 << i) | (1 << j) | (1 << k);
                for (int p = 0; p < X2.size(); ++p) {
                    if (state & X2[p]) continue;
                    for (int q = 0; q < X3.size(); ++q) {
                        if (state & X3[q]) continue;
                        if (X2[p] & X3[q]) continue;
                        if (cz[(1 << 21) - 1 - state - x - X2[p] - X3[q]]) ans &= state;
                    }
                }
            }
        }
    }
    X2.clear();
    X3.clear();
    X4.clear();
    for (int i = 0; i < 6; ++i) {
        if (ans & (1 << i)) X2.push_back(i);
    }
    for (int i = 6; i < 12; ++i) {
        if (ans & (1 << i)) X3.push_back(i);
    }
    for (int i = 12; i < 21; ++i) {
        if (ans & (1 << i)) X4.push_back(i);
    }
    if (X2.size() == 1) cout << (char)(X2[0] + 'A'); else cout << "?";
    if (X3.size() == 1) cout << (char)(X3[0] + 'A'); else cout << "?";
    if (X4.size() == 1) cout << (char)(X4[0] + 'A'); else cout << "?";
    cout << endl;

    return 0;
}
