#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 22;
const int MAXM = 30000;


int res, nodes, node, ans[MAXM][MAXN], new_ans[MAXM][MAXN];
int l[MAXN * 2], r[MAXN*2];


int split(int node) {
    res = 0;
    for (int i = 0; ans[i][0]; ++i) {
        int f = ans[i][node];
        for (int j = f - 1; j > (f - 1) / 2; --j)
         if (j <= ans[i][nodes]) {
             int k;
             for (k = 0; k < nodes; ++k) {
                 if (k >= node)
                     new_ans[res][k] = ans[i][k + 1];
                 else
                     new_ans[res][k] = ans[i][k];
             }
             new_ans[res][k] = j;
             new_ans[res++][k + 1] = f - j;
         }
    }
    ++nodes;
    memcpy(ans, new_ans, res * MAXN * 4);
    ans[res][0] = 0;
    cerr << res << endl;
    return 0;
}

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        int NN = 0;
        for (int i = 0; i < N; ++i) {
            string P;
            cin >> P;
            node = 0;
            for (int j = 0; j < P.size(); ++j)
             if (P[j] == '0') {
                 if (!l[node]) {
                     l[node] = ++NN;
                     r[node] = ++NN;
                 }
                 node = l[node];
             } else {
                 if (!r[node]) {
                     l[node] = ++NN;
                     r[node] = ++NN;
                 }
                 node = r[node];
             }
        }
        node = 0;
        nodes = 0;
        ans[0][0] = 100;
        ans[1][0] = 0;
        
        queue<int> step;
        step.push(0);
        while (!step.empty()) {
            int a = step.front();
            step.pop();
            if (l[a]) {
                split(node);
                step.push(r[a]);
                step.push(l[a]);
            } else {
                ++node;
            }
        }
        cout << "Case " << ++times << ": " << res << endl;
    }
    return 0;
}
