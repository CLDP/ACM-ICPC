struct TwoSAT {
    int n;
    vector<int> G[MAXN * 2];
    bool mark[MAXN * 2];
    int S[MAXN * 2], c;

    bool dfs(int x) {
        if (mark[x ^ 1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int i = 0; i < G[x].size(); ++i) 
            if (!dfs(G[x][i])) return false;
        return true;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; ++i) G[i].clear();
        memset(mark, 0, sizeof(mark));
    }

    // xv = 1 if x, 0 if ~x
    void add_clause(int x, int xv, int y, int yv) {
        x = x * 2 + xv;
        y = y * 2 + yv;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (mark[i] || mark[i + 1]) continue;
            c = 0;
            if (!dfs(i)) {
                while (c > 0) mark[S[--c]] = false;
                if (!dfs(i + 1)) return false;
            }
        }
        return true;
    }
};
