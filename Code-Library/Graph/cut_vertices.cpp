vector<int> x[MAXN];
int dfn[MAXN], low[MAXN];
bool z[MAXN];

int cut(int a, int f, int &time) {
    dfn[a] = low[a] = time; 
    int s = 0;
    bool flag = false;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == f) continue;
        if (dfn[x[a][i]] == 0) {
            cut(x[a][i], a, ++time);
            ++s;
            low[a] = min(low[a], low[x[a][i]]);
            if (low[x[a][i]] >= dfn[a]) flag = true;
        } else {
            low[a] = min(low[a], dfn[x[a][i]]);
        }
    }
    if ((f != -1 && flag) || (f == -1 && s > 1)) z[a] = true;
    return 0;
}
