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

const int MAXN = 500010;

int A[MAXN], B[MAXN];
bool C[MAXN];
int IN[MAXN], OUT[MAXN];
long long CNT[MAXN];


int main() {
    long long N;
    int M;
    cin >> N >> M;
    char P;
    for (int i = 1; i <= M; ++i) {
        scanf(" %c%d%d", &P, &A[i], &B[i]);
        if (P == 'L') C[i] = false; else C[i] = true;
        OUT[i] = 2;
        ++IN[A[i]];
        ++IN[B[i]];
    }
    queue<int> Q;
    for (int i = 1; i <= M; ++i)
     if (IN[i] == 0) Q.push(i);
    CNT[1] = N;
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        if (a == 0) break;
        CNT[A[a]] += CNT[a] / 2;
        CNT[B[a]] += CNT[a] / 2;
        if (CNT[a] & 1) {
            if (C[a]) ++CNT[B[a]]; else ++CNT[A[a]];
        }
        --IN[A[a]];
        --IN[B[a]];
        
        if (IN[A[a]] == 0) Q.push(A[a]);
        if (IN[B[a]] == 0 && B[a] != A[a]) Q.push(B[a]);
    }
    
    for (int i = 1; i <= M; ++i) {
        if (CNT[i] & 1) C[i] = !C[i];
      //  cout << i << " " << CNT[i] << endl;
        if (C[i]) printf("R"); else printf("L");
    }
    printf("\n");
    
    return 0;
}
