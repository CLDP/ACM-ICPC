#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int N;
unordered_map<int, int> C;
bool f[1 << 20], z[1 << 20];
int x[22][22];
int s[20][1 << 20];

bool DP(int a, int b) {
    if (z[a]) return f[a];
    
    int k = a - b;
    for (int i = 0; i < N; ++i) {
        if (a & (1 << i)) continue;
        s[i][a] = s[i][b] + x[i][C[k]];
    }
    
    z[a] = true;
    if (a == (1 << N) - 1) return f[a] = true;
    
    for (int i = 0; i < N; ++i) {
        if (!(a & (1 << i))) {
            if (s[i][a] > 0) f[a] |= DP(a + (1 << i), a);
            if (f[a]) return true;
        }
    }
    
    return f[a];
}

int main() {
    int T;
    cin >> T;
    for (int i = 0, j = 1; i < 21; ++i) {
        C[j] = i;
        j = j + j;
    }
    
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) cin >> x[i][j];
        
        int ans = 0;
        for (int j = 0; j < (1 << N); ++j) f[j] = z[j] = false;
         
        for (int i = 0; i < N; ++i)  DP(1 << i, 0);
        
        for (int j = 0; j < N; ++j) {
            if (f[1 << j]) {
                cout << j + 1 << " ";
                ++ans;
            }
        }
        
        if (ans == 0) cout << 0;
        cout << endl;
    }
    return 0;
}
