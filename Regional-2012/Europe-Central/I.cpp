#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 50010;

long long A[MAXN], B[MAXN], C[MAXN];
long long X[MAXM], Y[MAXM];

int main() {
    int T, N, M;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
        
        for (int i = 0; i < M; ++i) scanf("%I64d%I64d", &X[i], &Y[i]);
        
        int S = 1;
        for (int i = 0; i < N; ++i) {
            ++S;
            for (int j = 0; j < i; ++j) {
                if (A[i] == 0 && A[j] == 0) continue;
                if (B[i] == 0 && B[j] == 0) continue;
                if (A[i] != 0 && B[j] != 0 && A[i] * B[j] == A[j] * B[i]) continue;
                ++S;
            }
        }
        
        unordered_set<string> SS;
        for (int i = 0; i < M; ++i) {
            string P;
            for (int j = 0; j < N; ++j) {
                if (A[j] * X[i] + B[j] * Y[i] + C[j] > 0) P.push_back('0'); else P.push_back('1');
            }
            SS.insert(P);
        }
        if (SS.size() == S) cout << "PROTECTED" << endl; else cout << "VULNERABLE" << endl;
    }
    return 0;
}
