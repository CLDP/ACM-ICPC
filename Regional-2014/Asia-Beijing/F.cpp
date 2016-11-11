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

const long long INF = 1000000007;

int N, M;
int x[55][55];
long long f[55][8];

long long cal(int A, int B, int C) {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= M; ++i) {
        int T = 0;
        if (x[i][A]) T += 1;
        if (x[i][B]) T += 2;
        if (x[i][C]) T += 4;
        
        for (int j = 0; j < 8; ++j) {
            f[i][j] = (f[i - 1][j] + f[i - 1][j ^ T]) % INF;
        }
    }
    
    return f[M][7];
}


int main() {
    int T;
    cin >> T;
    for (int times = 1; times <= T; ++times) {
        cin >> N >> M;
        memset(x, 0, sizeof(x));
        for (int i = 1; i <= M; ++i) {
            int P, Q;
            cin >> P;
            for (int j = 0; j < P; ++j) {
                cin >> Q;
                x[i][Q] = true;
            }
        }
        long long ans = 0;
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j)
          for (int k = 1; k <= N; ++k) {
              ans = (ans + cal(i, j, k)) % INF;
          }
        
        cout << "Case #" << times << ": " << ans << endl;
    }
    return 0;
}
