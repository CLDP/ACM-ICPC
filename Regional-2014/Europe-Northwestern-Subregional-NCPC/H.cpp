#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 360000;

int N;
int x[400010], y[400010];
int p[200010], q[400010];

int nextt[200010];

int Get_Next() {
    int j = 0, k = -1;
    nextt[0] = -1;
    while (j < N) 
     if (k == -1 || p[j] == p[k]) {
         nextt[++j] = ++k;
     } else k = nextt[k];
    return 0;
}

int pos() {  // p in q
    Get_Next();
    int i = 0, j = 0;
    while (i < N && j < N + N)
     if (i == -1 || p[i] == q[j]) {
         ++i;
         ++j;
     } else i = nextt[i];
    if (i == N) return 1; else return -1;
}


int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) scanf("%d", &x[i]);
    for (int i = 0; i < N; ++i) scanf("%d", &y[i]);
    sort(x, x + N);
    sort(y, y + N);
    x[N] = x[0];
    y[N] = y[0];
    for (int i = 0; i < N; ++i) {
        p[i] = x[i + 1] - x[i];
        q[i] = y[i + 1] - y[i];
        if (p[i] < 0) p[i] += MAXN;
        if (q[i] < 0) q[i] += MAXN;
        q[i + N] = q[i];
    }
    
    if (pos() == 1) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
