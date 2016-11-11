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

const int MAXN = 200010;

char P[MAXN];
char Q[MAXN];

long long getL(long long A, long long M) {
    if (0 <= A && A < M) return A;
    if (A < -M - M - 2) {
        A = -((-A) % (M + M + 2));
    }
    if (A > M + M + M + 2) {
        A = A % (M + M + 2);
    }
    if (A < 0) {
        if (A == -1) return -1;
        return getL(-2 - A, M);
    } else {
        if (A == M) return M;
        return getL(2 * M - A, M);
    }
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        scanf("%s", P);
        int M = strlen(P);
        if (M == 1) {
            cout << "DIES" << endl;
            continue;
        }
        if (M % 2 == 0) {
            bool flag = true;
            for (int i = 0; i < M; ++i) flag &= (P[i] == '0');
            if (flag) cout << "DIES" << endl; else cout << "LIVES" << endl;
            continue;
        }
        
        long long K = 1LL << 50;
        for (int i = 0; i < 10; ++i) {
            K = (K % (4 * M + 4)) * (K % (4 * M + 4));
        }
        
        for (int i = 0; i < M; ++i) {
            int A = getL(i - K, M);
            int B = getL(i + K, M);
            bool ZERO = false;
            if (A == -1 || A == M) ZERO ^= 1; else ZERO ^= (P[A] == '0');
            if (B == -1 || B == M) ZERO ^= 1; else ZERO ^= (P[B] == '0');
            if (ZERO) Q[i] = '1'; else Q[i] = '0';
        }
        for (int i = 0; i < M; ++i) P[i] = Q[i];
        
        bool flag = true;
        for (int i = 0; i < M; ++i) flag &= (P[i] == '0');
        if (flag) cout << "DIES" << endl; else cout << "LIVES" << endl;
    }
    return 0;
}
