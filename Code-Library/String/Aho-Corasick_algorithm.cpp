const int MAXNODE = 10010;
const int SIGMASIZE = 26;

class AC {
public:
    int ch[MAXNODE][SIGMASIZE];
    int val[MAXNODE];
    int f[MAXNODE];
    int last[MAXNODE];
    int sz;
    AC() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        f[0] = val[0] = last[0] = 0;
    }
    void clear() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        f[0] = val[0] = last[0] = 0;
    }
    // can be generalized 
    int idx(char c) {
        return c - 'a';
    }

    // v is the additional information, nonzero
    void insert(char *s, int v) {
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; ++i) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void print(int j) {
        while (j > 0) {
            // If you need to count
            // You can pre-calculate the sum of val[j]
            // Or sometimes you have to go through all of them
            cout << j << " " << val[j] << endl;
            j = last[j];
        }
    }

    void find(char *P) {
        int n = strlen(P);
        int j = 0;
        for (int i = 0; i < n; ++i) {
            int c = idx(P[i]);
            // *** Don't need to do the following 
            // while (j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if (val[j]) {
                print(j);
            } else {
                if (last[j]) print(last[j]);
            }
        }
    }
    
    // Don't forget to call this function!!!!!
    void getFail() {
        queue<int> Q;
        f[0] = 0;
        for (int c = 0; c < SIGMASIZE; ++c) {
            int u = ch[0][c];
            if (u) {
                f[u] = 0;
                Q.push(u);
                last[u] = 0;
            }
        }
        while (!Q.empty()) {
            int r = Q.front();
            Q.pop();
            for (int c = 0; c < SIGMASIZE; ++c) {
                int u = ch[r][c];
                if (!u) {
                    // *** Because of this
                    ch[r][c] = ch[f[r]][c];
                    continue;
                }
                Q.push(u);
                int v = f[r];
                // *** Don't need this also
                // while (v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }
};
