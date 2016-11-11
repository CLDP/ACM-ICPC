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

struct node {
    long long a;
    int b, c;
    
    bool operator < (node const &B) const {
        return a > B.a;
    }
};

node X[200100]; 
vector<node> P, Q;

int main() {
    int N;
    long long M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        scanf("%I64d%d", &X[i].a, &X[i].b);
        X[i].c = i + 1;
    }
    sort(X, X + N);
    int k = 0;
    long long temp = 0;
    for (int i = 0; i < N; ++i) {
        temp += X[i].a;
        k = i + 1;
        if (temp >= M) break;
    }
    for (int i = 0; i < N; ++i) {
        if (X[i].b == 1) P.push_back(X[i]); else Q.push_back(X[i]);
    }
    int A = min((int)P.size(), k);
    int B = k - A;
    temp = 0;
    for (int i = 0; i < A; ++i) temp += P[i].a;
    for (int i = 0; i < B; ++i) temp += Q[i].a;
    
    while (temp < M) {
        temp += Q[B++].a;
        temp -= P[--A].a;
    }
    cout << k << " " << A << endl;
    for (int i = 0; i < A; ++i) printf("%d ", P[i].c);
    for (int i = 0; i < B; ++i) printf("%d ", Q[i].c); 
    printf("\n"); 
    
    return 0;
}
