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

const int MX[4] = {0, -1, 0, 1};
const int MY[4] = {-1, 0, 1, 0};

int f[2010][2010];

int main() {
    int N, M, P, Q;
    long long C;
    cin >> N >> M >> P >> Q >> C;
    --P;
    --Q;
    long long X = P + 2 * (C / 4), Y = Q - 2 * (C / 4);
    for (long long t = C / 4 * 4 + 1; t <= C; ++t) {
        X += t * MX[t % 4];
        Y += t * MY[t % 4];
    }
    
    X = (X % N + N) % N;
    Y = (Y % M + M) % M;
    
    
    memset(f, -1, sizeof(f));
    f[X][Y] = -2;
    int TT = N * M - 1;
    
    for (long long t = C; t >= 1LL; --t) {
        int D = (t + 2) % 4;
        int L = 0;
        if (t & 1) {
            if (t < N) L = t; else L = t % N + N;
        } else {
            if (t < M) L = t; else L = t % M + M;
        }
        int A = X, B = Y;
        for (int i = 0; i < L; ++i) {
            A = (A + N + MX[D]) % N;
            B = (B + M + MY[D]) % M;
            if (f[A][B] != -1) continue;
            
            --TT;
            f[A][B] = (t + 25) % 26;
        }
        if (TT == 0) break;
        X = A;
        Y = B;
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (f[i][j] == -1) printf("."); 
            if (f[i][j] == -2) printf("@");
            if (f[i][j] >= 0) printf("%c", (char)(f[i][j] + 'A'));
        }
        printf("\n");
    }
    
    return 0;
}
