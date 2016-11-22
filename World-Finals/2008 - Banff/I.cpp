#include <vector>
#include <queue>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 110;

struct Node {
    int id;
	// This is "a-z" based, easily become bigger
    Node *nxt[26], *fail;
} *root, MEMORY[MAXN], *que[MAXN];

struct back {
    int a, b, c, d;
    back(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}
};


int k = 0;
char msg[MAXM];
vector<string> ANS;
long long f[30][110][1024];
vector<back> g[30][110][1024];
vector<string> ansS;


void insert(int id, string str) {
    Node *p = root;
    for(int i = 0; i < str.size(); ++i) {
        int idx = str[i] - 'a';
        if (p->nxt[idx] == 0) {
            MEMORY[k].id = -1;
            MEMORY[k].fail = 0;
            memset(MEMORY[k].nxt, 0, sizeof(MEMORY[k].nxt));
            p->nxt[idx] = &MEMORY[k++];
        }
        p = p->nxt[idx];
    }
    p->id = id;
}

void AC() {
    int head = 0, tail = 0;
    root->fail = 0;
    que[tail++] = root;
    while (head < tail) {
        Node *tmp = que[head++];
        for (int i = 0; i < 26; ++i) {
            if (tmp->nxt[i] == 0) continue;
            if (tmp == root) {
                tmp->nxt[i]->fail = root;
            } else {
                Node *p;
                for (p = tmp->fail; p != 0; p = p->fail) {
                    if (p->nxt[i] != 0) {
                        tmp->nxt[i]->fail = p->nxt[i];
                        break;
                    }
                }
                if (p == 0) tmp->nxt[i]->fail = root;
            }
            que[tail++] = tmp->nxt[i];
        }
    }
}

int getNext(int a, int b) {
    Node *p = &MEMORY[a];
    while (p->nxt[b] == 0 && p != root) p = p->fail;
    p = p->nxt[b];
    if (p == 0) p = root;
    return p - root;
}

int cal(int a) {
    int ans = 0;
    for (Node *p = &MEMORY[a]; p != 0; p = p->fail) {
        if (p->id != -1) ans |= (1 << p->id);
    }
    return ans;
}

int dfs(int a, int b, int c, string P) {
    if (a == 0) {
        ansS.push_back(P);
        return 0;
    }
    for (int i = 0; i < g[a][b][c].size(); ++i) {
        back T = g[a][b][c][i];
        dfs(T.a, T.b, T.c, (char)(T.d + 'a') + P);
    }
    return 0;
}


int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        k = 0;
        root = &MEMORY[k++];
        memset(MEMORY[0].nxt, 0, sizeof(MEMORY[0].nxt));
        root->id = -1;
        set<string> SS;
        for (int i = 0; i < M; ++i) {
            string P;
            cin >> P;
            if (SS.find(P) != SS.end()) {
                --i, --M;
                continue;
            }
            insert(i, P);
            SS.insert(P);
        }
        AC();
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= N; ++i)
         for (int j = 0; j < k; ++j)
          for (int l = 0; l < (1 << M); ++l) g[i][j][l].clear();
          
        f[0][0][0] = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < k; ++j) {
                for (int l = 0; l < (1 << M); ++l) {
                    if (f[i][j][l] == 0) continue;
                    for (int p = 0; p < 26; ++p) {
                        int r = getNext(j, p), s = cal(r);
                        f[i + 1][r][l | s] += f[i][j][l];
                        g[i + 1][r][l | s].push_back(back(i, j, l, p));
                    }
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i < k; ++i) ans += f[N][i][(1 << M) - 1];
        cout << "Case " << ++times << ": " << ans << " suspects" << endl;
        if (ans > 42) continue;
        ansS.clear();
        for (int i = 0; i < k; ++i)
         if (f[N][i][(1 << M) - 1] > 0) dfs(N, i, (1 << M) - 1, "");
        sort(ansS.begin(), ansS.end());
        for (int i = 0; i < ans; ++i) cout << ansS[i] << endl;
    }
    
    return 0;
}
