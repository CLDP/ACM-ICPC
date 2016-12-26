int find(int x) {
    if (x != f[x]) f[x] = find(f[x]);
    return f[x];
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return ;
    f[x] = f[y] = (d[x] > d[y] ? f[x] : f[y]);
    d[x] = d[y] = d[x] + d[y];
}
