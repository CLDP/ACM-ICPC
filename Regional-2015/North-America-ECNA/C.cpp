#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

long long KM[11][11];
long long SM[11][11];

int ans = 0;
int N, M;
long long T;
bool R[10][10], C[10][10];
vector<pair<int, int> > X;


void dfs_mul(int n, long long sum) {
    if (n + 1 == M) {
        if (1 <= sum && sum <= N && !R[X[n].first][sum] && !C[X[n].second][sum]) ++ans;
        return ;
    }

    if (KM[N][M - n] < sum) return ;

    int a = X[n].first, b = X[n].second;
    for (int i = 1; i <= N; ++i) {
        if (R[a][i] || C[b][i]) continue;
        R[a][i] = C[b][i] = true;
        if (sum >= i && sum % i == 0) dfs_mul(n + 1, sum / i);
        R[a][i] = C[b][i] = false;
    }
}


void dfs_add(int n, long long sum) {
    if (n + 1 == M) {
        if (1 <= sum && sum <= N && !R[X[n].first][sum] && !C[X[n].second][sum]) ++ans;
        return ;
    }

    if (SM[N][M - n] < sum || M - n > sum) return ;

    int a = X[n].first, b = X[n].second;
    for (int i = 1; i <= N; ++i) {
        if (R[a][i] || C[b][i]) continue;
        R[a][i] = C[b][i] = true;
        if (sum > i) dfs_add(n + 1, sum - i);
        R[a][i] = C[b][i] = false;
    }
}


bool XX[11][11];
int dfs_X(int a, int b) {
    X.push_back(make_pair(a, b));
    XX[a][b] = false;
    if (XX[a - 1][b]) dfs_X(a - 1, b);
    if (XX[a + 1][b]) dfs_X(a + 1, b);
    if (XX[a][b - 1]) dfs_X(a, b - 1);
    if (XX[a][b + 1]) dfs_X(a, b + 1);
    return 0; 
}

int main() {
    char op;
    cin >> N >> M >> T >> op;
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        XX[A][B] = true;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (XX[i][j]) dfs_X(i, j);
        }
    }

    if (op == '-' || op == '/') {
        for (int i = 1; i <= N; ++i)
         for (int j = i + 1; j <= N; ++j) {
             if (op == '-') {
                  if (abs(i - j) == T) ans += 2;
             } else {
                  if (j % i == 0 && j / i == T) ans += 2;
             }
         }
        cout << ans << endl;
        return 0;
    }

    for (int i = 1; i <= 9; ++i) {
        KM[i][0] = 1;
        SM[i][0] = 0;
        for (int j = 1; j <= 10; ++j) {
            KM[i][j] = KM[i][j - 1] * i;
            SM[i][j] = SM[i][j - 1] + i;
        }
    }

    if (op == '+') dfs_add(0, T); else dfs_mul(0, T);

    cout << ans << endl;
    return 0;
}
