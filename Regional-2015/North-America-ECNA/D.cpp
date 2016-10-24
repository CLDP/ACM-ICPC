#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
string P[110];
int f[110][110];

bool check(int a, int b) {
    if (P[a][b] == '.') return false;
    if (a == 0 || a == N - 1 || b == 0 || b == M - 1) return true;
    if (P[a - 1][b] == '.') return true;
    if (P[a + 1][b] == '.') return true;
    if (P[a][b + 1] == '.') return true;
    if (P[a][b - 1] == '.') return true;
    return false;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> P[i];
    queue<pair<int, int> > Q;
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < M; ++j) {
          if (check(i, j)) {
              Q.push(make_pair(i, j));
              f[i][j] = 1;
          }
     }

    while (!Q.empty()) {
        int a = Q.front().first;
        int b = Q.front().second;
        Q.pop();
        if (a > 0 && f[a - 1][b] == 0 && P[a - 1][b] == 'T') {
            Q.push(make_pair(a - 1, b));
            f[a - 1][b] = f[a][b] + 1;
        }
        if (a < N - 1 && f[a + 1][b] == 0 && P[a + 1][b] == 'T') {
            Q.push(make_pair(a + 1, b));
            f[a + 1][b] = f[a][b] + 1;
        }
        if (b > 0 && f[a][b - 1] == 0 && P[a][b - 1] == 'T') {
            Q.push(make_pair(a, b - 1));
            f[a][b - 1] = f[a][b] + 1;
        }
        if (b < M - 1 && f[a][b + 1] == 0 && P[a][b + 1] == 'T') {
            Q.push(make_pair(a, b + 1));
            f[a][b + 1] = f[a][b] + 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) ans = max(ans, f[i][j]);

    if (ans < 10) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (f[i][j] == 0) {
                    cout << "..";
                } else {
                    cout << "." << f[i][j];
                }
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (f[i][j] == 0) {
                    cout << "...";
                } else 
                if (f[i][j] < 10) {
                    cout << ".." << f[i][j];
                } else {
                    cout << "." << f[i][j];
                }
            }
            cout << endl;
        }
    }
    
    return 0;
}
