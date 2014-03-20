#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int x[22], y[22];
bool z[22];
int N, M, T, ans;
vector<int> ansT;
vector<int> S[22];

int dfs(int a, int b) {
    if (b == 0) {
        int temp = 0;
        for (int i = 1; i <= N; ++i) {
            if (z[i]) temp += x[i];
        }
        for (int i = 0; i < T; ++i) {
            bool flag = false;
            for (int j = 0; j < S[i].size(); ++j) {
                flag |= z[S[i][j]];
                if (flag) break;
            }
            if (flag) temp += y[i];
        }
        if (ans < temp) {
            ans = temp;
            ansT.clear();
            for (int i = 1; i <= N; ++i) 
             if (z[i]) ansT.push_back(i);
        }
        return 0;
    }
    if (a == N + 1) return 0;
    if (a + b - 1 > N) return 0;
    
    z[a] = true;
    dfs(a + 1, b - 1);
    z[a] = false;
    dfs(a + 1, b);
    return 0;
}


int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) cin >> x[i];
        cin >> T;
        for (int i = 0; i < T; ++i) {
            int A;
            cin >> A;
            S[i] = vector<int>(A, 0);
            for (int j = 0; j < A; ++j) cin >> S[i][j];
            cin >> y[i];
            for (int j = 0; j < A; ++j) x[S[i][j]] -= y[i];
        }
        ans = 0;
        dfs(1, M);
        
        cout << "Case Number  " << ++times << endl;
        cout << "Number of Customers: " << ans << endl;
        cout << "Locations recommended:";
        for (int i = 0; i < M; ++i) cout << " " << ansT[i];
        cout << endl << endl;
    }
    return 0;
}
