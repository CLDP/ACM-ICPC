#include <cstdio>
#include <cstring>

const int MAXN = 1010;

int l[MAXN], x[MAXN][MAXN];
bool z[MAXN];

bool find(int v, int M) {
    int k;
    for (int i = 1; i <= M; ++i) {
        if (!z[i] && x[v][i]) {
            z[i] = 1;
            k = l[i];
            l[i] = v;
            if (!k || find(k, M)) return 1;
            l[i] = k;
        }
    }
    return 0;
}

int main() {
    int N, M, E;
    int a, b, ans;
    scanf("%d%d%d", &N, &M, &E);
    for (int i = 0; i < E; ++i) {
        scanf("%d%d", &a, &b);
        x[a][b] = 1;
    } 
    for (int i = 1; i <= N; ++i) {
        memset(z, 0, sizeof(z));
        find(i, M);
    }
    ans = 0;
    for (int i = 1; i <= M; ++i) ans += (l[i] > 0);
    
    printf("%d\n", ans);
    return 0;
}
