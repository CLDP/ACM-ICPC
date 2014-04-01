#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};
const int INF = 1000000000;

int N, M;
vector<pair<int, int> > X;
bool x[210][210], z[210][210];

int TRY(int a, int b, int c) {
    int a1 = a + MX[c], b1 = b + MY[c], a2 = a + MX[(c + 1) % 4], b2 = b + MY[(c + 1) % 4];
    if (z[a1][b1] || z[a2][b2]) return INF;
    
    int left = X.size() - 1;
    if (1 <= a1 && a1 <= N && 1 <= b1 && b1 <= M) --left;
    if (1 <= a2 && a2 <= N && 1 <= b2 && b2 <= M) --left;
    
    memset(x, 0, sizeof(x));
    x[a][b] = x[a1][b1] = x[a2][b2] = true;
    
    if (left == 0) return 1;
    
    int T = X.size();
    for (int k = 1; k < T; ++k) {
        vector<int> S(T - k, 0);
        for (int i = 0; i < k; ++i) S.push_back(1);
        bool flag = false;
        while (S[0] == 0 || flag) {
            bool temp = true;
            int LN = left;
            for (int i = 0; i < T; ++i) {
                if (S[i] == 0) continue;
                int p = X[i].first, q = X[i].second;
                if (a == p && b == q) temp = false;
                if (z[p - 1][q] || z[p][q + 1]) {
                    temp = false;
                } else {
                    if (!x[p][q]) x[p][q] = true, --LN;
                    if (p - 1 > 0 && !x[p - 1][q]) x[p - 1][q] = true, --LN;
                    if (q + 1 <= M && !x[p][q + 1]) x[p][q + 1] = true, --LN;
                }
            }
            
            if (temp && LN == 0) return 1 + k;
            
            for (int i = 0; i < T; ++i) x[X[i].first][X[i].second] = false;
            x[a][b] = x[a1][b1] = x[a2][b2] = true;
            
            next_permutation(S.begin(), S.end());
            if (S[0] == 1) flag = true;
            if (S[0] == 0 && flag) break;
        }
    }
    return INF;
}

int main() {
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        X.clear();
        memset(z, 0, sizeof(z));
        for (int i = 0; i < N; ++i) {
            string P;
            cin >> P;
            for (int j = 0; j < M; ++j) {
                if (P[j] == '.') {
                    z[i + 1][j + 1] = false; 
                    X.push_back(make_pair(i + 1, j + 1));
                } else {
                    z[i + 1][j + 1] = true;
                }
            }
        }
        
        if (X.size() == 0) {
            cout << 0 << endl;
            continue;
        }
        
        int ans = INF;
        for (int i = 0; i < X.size(); ++i) {
            int a = X[i].first, b = X[i].second;
            ans = min(ans, TRY(a, b, 0));
            ans = min(ans, TRY(a, b, 1));
            ans = min(ans, TRY(a, b, 2));
            ans = min(ans, TRY(a, b, 3));
        }
        if (ans == INF) ans = -1;
        cout << ans << endl;
    }
    return 0;
}
