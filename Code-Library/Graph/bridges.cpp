vector<int> x[MAXN];
int dfn[MAXN], low[MAXN];
bool z[MAXN][MAXN];

void bridges(int a, int f, int &times) {
    dfn[a] = low[a] = times; 
    int s = 0;
    bool flag = false;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == f) continue;
        if (dfn[x[a][i]] == 0) {
            bridges(x[a][i], a, ++times);
            ++s;
            low[a] = min(low[a], low[x[a][i]]);
            // This is a bridge
            if (low[x[a][i]] == dfn[x[a][i]]) z[x[a][i]][a] = z[a][x[a][i]] = true;
        } else {
            low[a] = min(low[a], dfn[x[a][i]]);
        }
    }
}
