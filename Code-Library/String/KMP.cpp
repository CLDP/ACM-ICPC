void getFail(char *P, int *f) {
    int m = strlen(P);
    f[0] = f[1] = 0;
    for (int i = 1; i < m; ++i) {
        int j = f[i];
        while (j && P[i] != P[j]) j = f[j];
        f[i + 1] = P[i] == P[j] ? j + 1 : 0;
    }
}

// Find Q in P
int find(char *P, char *Q, int *f) {
    int n = strlen(P), m = strlen(Q);
    getFail(Q, f);
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j && Q[j] != P[i]) j = f[j];
        if (Q[j] == P[i]) ++j;
        if (j == m) return i - m + 1;
    }
    return -1;
}
