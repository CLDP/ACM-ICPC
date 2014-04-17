#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct node {
    int a, b, c;
};

bool compare01(const node &A, const node &B) {
    return A.c < B.c;
}

bool compare10(const node &A, const node &B) {
    return A.c > B.c;
}


int N, M;
int f[MAXN], d[MAXN];
node X[MAXN];

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}

int Kruskal() {
    for (int i = 1; i <= N; ++i) {
        f[i] = i;
        d[i] = 1;
    }
    int ans = 0, add = 1;
    for (int i = 0; i < M; ++i) {
        int a = X[i].a, b = X[i].b;
        if (find(a) == find(b)) continue;
        Union(a, b);
        ++add;
        ans += X[i].c;
    }
    if (add == N) return ans; else return -1;
}

bool check(int A, int B) {
    if (A <= 1 && 1 <= B) return true;
    int a = 1, b = 1;
    while (b <= B) {
        int c = a + b;
        a = b;
        b = c;
        if (A <= b && b <= B) return true;
    }
    return false;
}

int main() {
    int TT;
    cin >> TT;
    for (int times = 1; times <= TT; ++times) {
        scanf("%d%d", &N, &M);
        for (int i = 0; i < M; ++i) scanf("%d%d%d", &X[i].a, &X[i].b, &X[i].c);
        sort(X, X + M, compare01);
        int A = Kruskal();
        sort(X, X + M, compare10);
        int B = Kruskal();
        cout << "Case #" << times << ": ";
        if (check(A, B)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
