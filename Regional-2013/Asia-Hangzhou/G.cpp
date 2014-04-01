#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int MAXM = 61;

long long mm[MAXM];

struct Node {
    int son[2], size;
    long long val;
    void init(){
        son[0] = son[1] = -1;
        size = 0;
        val = -1;
    }
};

struct Edge{
    int v, next;
    long long len;
};

struct Query{
    int k;
    int id;
    bool operator < (const Query & A) const {
        return k < A.k;
    }
};


int n, m, L, root, tot, Cnter;
int head[MAXN];
Node node[MAXN * MAXM + 1];
Edge edge[MAXN << 1];
long long value[MAXN], ans[MAXN];
Query q[MAXN];


struct Pointer{
    int k;
    long long val, id;
    bool operator < (const Pointer & A) const {
        return val < A.val;
    }
    bool movenext(){
        ++k;
        if (k >= n) return false;
        int kk = k;
        int now = root;
        int dep = 60;
        while (node[now].val == -1) {
            int f = ((id & mm[dep]) != 0) ^ 1;
            --dep;
            if (node[now].son[f] != -1 && node[node[now].son[f]].size >= kk) {
                now = node[now].son[f];
            } else
            if (node[now].son[f] != -1 && node[node[now].son[f]].size < kk) {
                kk -= node[node[now].son[f]].size;
                now = node[now].son[1 - f];
            } else {
                now = node[now].son[1 - f];
            }
        }
        val = id ^ node[now].val;
        return true;
    }
};

priority_queue<Pointer> Q;

int newNode(){
    node[L].init();
    return L++;
}

int insertTrie(long long x){
    int now = root;
    node[root].size++;
    for (int i = MAXM - 1 ; i >= 0; --i) {
        int r = (x & mm[i]) > 0;
        if (node[now].son[r] == -1) node[now].son[r] = newNode();
        now = node[now].son[r];
        node[now].size++;
    }
    node[now].val = x;
    return 0;
}

int addedge(int x, int y, long long z) {
    edge[tot].next = head[x];
    edge[tot].v = y;
    edge[tot].len = z;
    head[x] = tot++;
    return 0;
}

void dfs(int u, int v, long long now) {
    insertTrie(now);
    value[Cnter++] = now;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int to = edge[i].v; 
        long long len = edge[i].len;
        if (to == v) continue;
        dfs(to, u, now ^ len);
    }
}

int solve(){
    memset(head, -1, sizeof(head));
    tot = 0;
    for (int i = 0; i < n - 1; ++i) {
        int x, y; 
        long long z;
        cin >> x >> y >> z;
        addedge(x, y, z);
        addedge(y, x, z);
    }
    L = 0;
    root = newNode();
    Cnter = 0;
    dfs(1, -1, 0);
    cin >> m;
    for (int i = 0; i < m; ++i) {
        scanf("%d", &q[i].k);
        q[i].id = i;
    }
    sort(q, q + m);
    while (!Q.empty()) Q.pop();
    for (int i = 0; i < n; ++i) {
        Pointer now;
        now.k = 0;
        now.id = value[i];
        if (now.movenext()) Q.push(now);
    }

    int rank = 0;
    for (int i = 0; i < m; ++i) {
        long long ret = 0;
        while (!Q.empty() && rank < q[i].k) {
            ++rank;
            Pointer p = Q.top();
            Q.pop();
            ret = p.val;
            if (p.movenext()) Q.push(p);
        }
        if (Q.empty()) 
            ans[q[i].id] = -1;
        else 
            ans[q[i].id] = ret;
    }
    for (int i = 0; i < m; ++i) printf("%lld\n" , ans[i]);
    return 0;
}

int main() {
    for (int i = 0; i < MAXM; ++i) mm[i] = 1ll << i;
    while (cin >> n) {
        if (n == 0) break;
        solve();
    }
    return 0;
}
