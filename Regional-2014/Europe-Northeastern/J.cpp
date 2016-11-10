#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
string P;
vector<int> X;
int x[110];
bool z[110];

bool dfs(int a) {
    if (a == N) {
        for (int i = 0; i < M; ++i) {
            if (x[i] == 0) continue;
            cout << x[i] << " ";
        }
        cout << endl;
        return true;
    }
    if (X[a] < 10) {
        for (int i = 0; i < M; ++i) {
            if (z[i]) continue;
            if (P[i] - '0' == X[a]) {
                x[i] = X[a];
                z[i] = true;
                if (dfs(a + 1)) return true;
                x[i] = 0;
                z[i] = false;
            }
        }
    } else {
        for (int i = 0; i < M - 1; ++i) {
            if (z[i] || z[i + 1]) continue;
            int T = P[i] - '0';
            T = T * 10 + P[i + 1] - '0';
            if (T == X[a]) {
                x[i] = X[a];
                z[i] = z[i + 1] = true;
                if (dfs(a + 1)) return true;
                x[i] = 0;
                z[i] = z[i + 1] = false;
            }
        }
    }
    return false;
}

int main() {
    freopen("joke.in", "r", stdin);
    freopen("joke.out", "w", stdout);
    cin >> P;
    M = P.size();
    N = 0;
    for (int i = 1; ; ++i) {
        if (i < 10) N += 1; else N += 2;
        if (N == M) {
            N = i;
            break;
        }
        
    }
    
    for (int i = 5; i >= 1; --i) {
        if (10 * i <= N) X.push_back(10 * i);
    }
    
    for (int i = 9; i >= 1; --i) {
        if (40 + i <= N) X.push_back(40 + i);
        if (30 + i <= N) X.push_back(30 + i);
        if (20 + i <= N) X.push_back(20 + i);
        if (10 + i <= N) X.push_back(10 + i);
        if (i <= N) X.push_back(i);
    }
    
    dfs(0);
    
    return 0;
}
