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

const int MAXN = 365 * 24 * 60;

int D[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct node {
    long long mark;
    long long best;
};

node segt[MAXN * 4];

void insert(int x, int l, int r, int ind, long long v) {
    int k = (l + r) / 2;
    if (ind <= l) {
        segt[x].mark += v;
        segt[x].best += v;
        return;
    }
    if (segt[x].mark != 0) {
        segt[x*2].mark += segt[x].mark;
        segt[x*2].best += segt[x].mark;
        segt[x*2+1].mark += segt[x].mark;
        segt[x*2+1].best += segt[x].mark;
        segt[x].mark = 0;
    }
    if (ind <= k) insert(x * 2, l, k, ind, v);
    insert(x * 2 + 1, k + 1, r, ind, v);
    segt[x].best = max(segt[x*2].best, segt[x*2+1].best);
}

int cnt(string P) {
    int N = 0;
    int A = (P[0] - '0') * 10 + (P[1] - '0');
    int B = (P[3] - '0') * 10 + (P[4] - '0');
    for (int i = 0; i < B; ++i) N += D[i];
    N += A;
    return N - 1;
}

map<int, long long> C1, C2;

int main() {
    int N, A;
    char P[20], Q[20];
    scanf("%d", &N);
    long long ans = 0;
    
    for (int i = 0; i < N; ++i) {
        scanf("%d %s %s", &A, P, Q);
        int T = 0;
        T += (Q[0] - '0') * 600 + (Q[1] - '0') * 60 + (Q[3] - '0') * 10 + (Q[4] - '0');
        T += cnt(P) * 24 * 60;
        ans += A;
        insert(1, 1, MAXN, MAXN - T, A);
        
        printf("%I64d\n", ans - max(0LL, segt[1].best));
    }
    return 0;
}
