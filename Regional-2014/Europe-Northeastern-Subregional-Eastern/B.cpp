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

vector<int> e[100005];
int n;
int k[100005];
int kp[100005];
void DFS(int ind, int prev) {
    bool cont = true;
    if (prev == kp[ind])
        cont = false;
    else 
    if (prev != kp[ind]) {
        if (kp[ind] == -1)
            kp[ind] = prev;
        else 
        if (kp[ind] == -2)
            cont = false;
        else {
            kp[ind] = -2;
            if (k[ind] != 0) cont = false;
        }
    }
    if (cont) {
        int next = prev;
        if (k[ind] != 0) next = k[ind];
        for (int i = 0; i < e[ind].size(); ++i) DFS(e[ind][i], next);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
        kp[i] = -1;
        int m;
        cin >> m;
        e[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> e[i][j];
    }
    
    DFS(1, 0);
    
    for (int i = 1; i <= n; ++i) {
        if (kp[i] == 0)
            cout << "sober";
        else 
        if (kp[i] == -2)
            cout << "unknown";
        else
            cout << kp[i];
        cout << " ";
        if (k[i] != 0)
            cout << k[i];
        else 
        if (kp[i] == 0)
            cout << "sober";
        else 
        if (kp[i] == -2)
            cout << "unknown";
        else
            cout << kp[i];
        cout << endl;
    }

    return 0;
}
