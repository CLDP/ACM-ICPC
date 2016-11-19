vector<int> x[MAXN];
int dfn[MAXN], low[MAXN];
stack<int> S;
int blocknum;

// point biconnected
// edge biconnected is just removing bridges
// one single edge or one vertex is a biconnected component
int block(int a, int f, int &time) {
    dfn[a] = low[a] = time; 
    S.push(a);
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == f) continue;
        if (dfn[x[a][i]] == 0) {
            block(x[a][i], a, ++time);
            low[a] = min(low[a], low[x[a][i]]);
            if (low[x[a][i]] >= dfn[a]) {
                while (S.top() != x[a][i]) {
                    cout << S.top() << " ";
                    S.pop();
                }
                cout << S.top() << " " << a << endl;
                S.pop();
                ++blocknum;
            }
        } else {
            low[a] = min(low[a], dfn[x[a][i]]);
        }
    }
    return 0;
}
