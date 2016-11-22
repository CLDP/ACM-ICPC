#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 502;
const int INF = 1000000000;

int N;
int x[MAXN], f[MAXN][MAXN], g[MAXN];
bool cz[MAXN][MAXN], h[MAXN][MAXN];


int dp(int a, int b) {
    if (cz[a][b]) return f[a][b];
    cz[a][b] = true;
    if (a == b) return f[a][b] = 0;
    if (a + 1 == b) return f[a][b] = 1;
    
    vector<int> C, K;
    C.reserve(b - a + 1);
    K.reserve(b - a + 1);
    for (int i = a; i <= b; ++i) C.push_back(x[i]);
    sort(C.begin(), C.end());
    for (int i = a; i <= b; ++i) K.push_back(lower_bound(C.begin(), C.end(), x[i]) - C.begin());
    stack<int> R;
    R.push(K[b - a]);
    for (int i = b - 1; i > a; --i) R.push(min(R.top(), K[i - a]));
    
    int L = K[0];
    for (int k = a; k < b; ++k) {
        L = min(L, K[k - a]);
        int LM = min(L, R.top()), RM = max(L, R.top());
        f[a][b] = min(f[a][b], dp(a, k) + dp(k+1, b) + b - a + 1 - RM + LM);
        R.pop();
    }
    return f[a][b];
}


int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> x[i];
    
    for (int i = 1; i <= N; ++i)
     for (int j = i; j <= N; ++j) f[i][j] = INF;
    
    for (int i = 1; i <= N; ++i) {
        vector<bool> z(N + 1, false);
        int maxN = 0;
        for (int j = i; j <= N; ++j) {
            if (z[x[j]]) break;
            z[x[j]] = true;
            maxN = max(maxN, x[j]);
            if (maxN == j - i + 1) {
                dp(i, j);
                h[i][j] = true;
            }
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        g[i] = INF;
        for (int j = 1; j <= i; ++j) 
         if (h[j][i]) g[i] = min(g[i], g[j-1] + f[j][i]);
    }
    
    if (g[N] == INF) 
        cout << "impossible" << endl;
    else
        cout << g[N] << endl;
    
    return 0;
}
