#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int MAXM = 2010;

string Q;
int QS;
string X[MAXN];
bool S[MAXN];
int Y[MAXN], Z[MAXN];
int f[MAXN][MAXM];
bool z[MAXN][MAXM];

int DP(int a, int b) {
    if (z[a][b]) return f[a][b];
    z[a][b] = true;
    if (!S[a]) {
        int c = b;
        for (int i = 0; i < X[a].size(); ++i) {
            if (c == QS) break;
            if (X[a][i] == Q[c]) ++c;
        }
        f[a][b] = c;
    } else {
        int c = DP(Y[a], b);
        f[a][b] = DP(Z[a], c);
    }
    return f[a][b];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M = 0;
        cin >> N;
        unordered_map<string, int> C;
        string P;
        getline(cin, P);
        for (int i = 0; i < N; ++i) {
            getline(cin, P);
            if (P.find('+') != string::npos) {
                string Q1, Q2, Q3, QQ;
                istringstream PP(P);
                PP >> Q1 >> QQ >> Q2 >> QQ >> Q3;
                if (C.find(Q1) == C.end()) C[Q1] = ++M;
                if (C.find(Q2) == C.end()) C[Q2] = ++M;
                if (C.find(Q3) == C.end()) C[Q3] = ++M;
                int a = C[Q1], b = C[Q2], c = C[Q3];
                Y[a] = b;
                Z[a] = c;
                S[a] = true;
            } else {
                string Q1, Q2, QQ;
                istringstream PP(P);
                PP >> Q1 >> QQ >> Q2;
                if (C.find(Q1) == C.end()) C[Q1] = ++M;
                int a = C[Q1];
                X[a] = Q2;
                S[a] = false;
            }
        }
        cin >> P >> Q;
        QS = Q.size();
        for (int i = 1; i <= M; ++i)
         for (int j = 0; j <= QS; ++j) {
             f[i][j] = 0;
             z[i][j] = 0;
         }
        
        if (DP(C[P], 0) == QS) cout << "YES" << endl; else cout << "NO" << endl;
    }
    return 0;
}
