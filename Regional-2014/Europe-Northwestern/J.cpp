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

bool BF = true;
int NN = 0;
int A[10010], B[10010];
vector<int> x[10010];

int dfs(int a, int b, int c) {
    if (b == -1) {
        A[a] = ++NN;
        B[a] = ++NN;
    } else {
        A[a] = c;
        B[a] = ++NN;
    }
    
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == b) continue;
        if (BF) {
            BF = false;
            dfs(x[a][i], a, A[a]);
        } else 
            dfs(x[a][i], a, B[a]);
    }
    
    return 0;
}

int main() {
    int N, a, b;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        scanf("%d%d", &a, &b);
        x[a].push_back(b);
        x[b].push_back(a);
    }
    if (N == 2) {
        cout << "1 2\n1 2" << endl;
        return 0;
    }
    for (int i = 1; i <= N; ++i) {
        if (x[i].size() == 1) continue;
        dfs(i, -1, -1);
        break;
    }
    for (int i = 1; i <= N; ++i) cout << A[i] << " " << B[i] << endl;
    return 0;
}
