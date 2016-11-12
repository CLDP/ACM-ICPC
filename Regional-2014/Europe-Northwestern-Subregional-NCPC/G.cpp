#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int temp;
bool flag = true;
int N, M, A, B, C;
int x[200010];
vector<int> X[200010];

int fill(int a) {
    for (int j = 0; j < X[a].size(); ++j) {
        int b = X[a][j];
        if (x[b] == x[a]) {
            flag = false;
            return 0;
        }
        if (x[b] == -x[a]) continue;
        x[b] = -x[a];
        if (x[b] == 1) ++temp;
        fill(b);
    }
    return 0;
}

int fillzero(int a) {
    for (int j = 0; j < X[a].size(); ++j) {
        int b = X[a][j];
        if (x[b] != 0) {
            x[b] = 0;
            fillzero(b);
        }
    }
    return 0;
}


bool dfs(int a) {
    if (a == N + 1) return true;
    if (x[a] != 0) return dfs(a + 1);
    
    int TEMP = 1000000, SAT = 0;
    
    flag = true;
    temp = 1;
    x[a] = 1;
    fill(a);
    if (flag && temp < TEMP) {
        TEMP = temp;
        SAT = 1;
    }
    x[a] = 0;
    fillzero(a);
    
    
    flag = true;
    temp = 0;
    x[a] = -1;
    fill(a);
    if (flag && temp < TEMP) {
        TEMP = temp;
        SAT = -1;
    }
    fillzero(a);
    
    if (SAT == 0) return false;
    
    x[a] = SAT;
    fill(a);
    
    return dfs(a + 1);
}



int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &A, &B, &C);
        if (C == 2) {
            if (x[A] == -1 || x[B] == -1) {
                flag = false;
                break;
            }
            x[A] = x[B] = 1;
        }
        if (C == 0) {
            if (x[A] == 1 || x[B] == 1) {
                flag = false;
                break;
            }
            x[A] = x[B] = -1;
        }
        if (C == 1) {
            if (x[A] == 1) {
                if (x[B] == 1) {
                    flag = false;
                    break;
                }
                x[B] = -1;
                continue;
            }
            if (x[A] == -1) {
                if (x[B] == -1) {
                    flag = false;
                    break;
                }
                x[B] = 1;
                continue;
            }
            if (x[B] == 1) {
                if (x[A] == 1) {
                    flag = false;
                    break;
                }
                x[A] = -1;
                continue;
            }
            if (x[B] == -1) {
                if (x[A] == -1) {
                    flag = false;
                    break;
                }
                x[A] = 1;
                continue;
            }
            X[A].push_back(B);
            X[B].push_back(A);
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        if (x[i] != 0 && X[i].size() != 0) fill(i);
    }
    
    flag &= dfs(1);
    
    int ans = 0;
    for (int i = 1; i <= N; ++i) 
     if (x[i] == 1) ++ans;
    
    if (flag) {
        cout << ans << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
