#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXT = 1440;
const string KM[7] = {
    ".XX......XX..XX......XX..XX..XX..XX..XX.....", 
    "X..X...X...X...XX..XX...X......XX..XX..X....", 
    "X..X...X...X...XX..XX...X......XX..XX..X....", 
    ".........XX..XX..XX..XX..XX......XX..XX.....", 
    "X..X...XX......X...X...XX..X...XX..X...X....", 
    "X..X...XX......X...X...XX..X...XX..X...X....", 
    ".XX......XX..XX......XX..XX......XX..XX....."
};

int N;
vector<string> X[MAXN];


vector<string> getN(int N) {
    vector<string> ans;
    for (int i = 0; i < 7; ++i) ans.push_back(KM[i].substr(N * 4, 4));
    return ans;
}

void getT(int T, int Z[]) {
    T %= MAXT;
    Z[1] = T / 60;
    if (Z[1] > 9) {
        Z[0] = Z[1] / 10;
        Z[1] %= 10;
    } else {
        Z[0] = 10;
    }
    Z[3] = T % 60;
    Z[2] = Z[3] / 10;
    Z[3] %= 10;
}

// ans, true values, output values
bool update(vector<string> &ans, vector<string> &app, vector<string> P, vector<string> Q) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (ans[i][j] == '.') continue;
            if (Q[i][j] == '.') {
                switch (app[i][j]) {
                    case '.': 
                    case '0': app[i][j] = '0'; break;
                    default : app[i][j] = '2'; break;
                }
            } else {
                switch (app[i][j]) {
                    case '.': 
                    case '1': app[i][j] = '1'; break;
                    default : app[i][j] = '2'; break;
                }
            }
            if (P[i][j] == Q[i][j]) {
                if (ans[i][j] == 'W') continue;
                if (ans[i][j] == 'X' && P[i][j] != 'X') return false;
                if (ans[i][j] == 'Y' && P[i][j] != '.') return false;
            } else {
                if (ans[i][j] == 'W') {
                    if (Q[i][j] == 'X') ans[i][j] = 'X'; else ans[i][j] = 'Y';
                    continue;
                }
                if (ans[i][j] == 'X' && Q[i][j] == '.') return false;
                if (ans[i][j] == 'Y' && Q[i][j] == 'X') return false;
            }
        }
    }
    return true;
}

vector<string> tryT(int T) {
    vector<string> ans = getN(8);
    vector<string> app;
    for (int i = 0; i < 7; ++i) {
        string P = ans[i] + "." + ans[i] + "..." + ans[i] + "." + ans[i];
        if (i == 2 || i == 4) P[10] = 'X';
        for (int j = 0; j < P.size(); ++j) {
            if (P[j] == 'X') P[j] = 'W';
        }
        ans[i] = P;
        app.push_back(string(21, '.'));
    }

    for (int i = T; i < T + N; ++i) {
        int Z[4];
        getT(i, Z);
        vector<string> Y[4];
        for (int j = 0; j < 4; ++j) Y[j] = getN(Z[j]);
        vector<string> temp;
        for (int j = 0; j < 7; ++j) {
            string Q = Y[0][j] + "." + Y[1][j] + "..." + Y[2][j] + "." + Y[3][j];
            if (j == 2 || j == 4) Q[10] = 'X';
            temp.push_back(Q);
        }
        if (!update(ans, app, temp, X[i - T])) {
            ans.clear();
            return ans;
        }
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (app[i][j] == '2' && ans[i][j] != 'W') {
                ans.clear();
                return ans;
            }
            if (app[i][j] != '2' && ans[i][j] == 'W') ans[i][j] = '?';
        }
    }
    return ans;
}

int main() {
    cin >> N;
    string P;
    for (int i = 0; i < N; ++i) {
        getline(cin, P);
        for (int j = 0; j < 7; ++j) {
            getline(cin, P);
            X[i].push_back(P);
        }
    }

    vector<vector<string> > ansT;
    for (int i = 0; i < MAXT; ++i) {
        vector<string> temp = tryT(i);
        if (temp.empty()) continue;
        ansT.push_back(temp);
    }

    if (ansT.empty()) {
        cout << "impossible" << endl;
        return 0;
    }
    vector<string> ans = ansT[0];
    for (int k = 1; k < ansT.size(); ++k) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 21; ++j) {
                if (ans[i][j] != ansT[k][i][j]) {
                    ans[i][j] = '?';
                }
            }
        }
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (ans[i][j] == 'X') ans[i][j] = '1';
            if (ans[i][j] == 'Y') ans[i][j] = '0';
        }
    }
    for (int i = 0; i < 7; ++i) cout << ans[i] << endl;

    return 0;
}
