#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 76;
const int MAXM = 100010;
const int INF = 1000000000;

struct node {
    int v, d;
};


int n, total;
bool y[MAXN], z[MAXN];
vector<int> x[MAXN];
node xx[MAXN];


bool compare(const node &a, const node &b) {
    return a.d > b.d;
}


int dfs(int a, int b) {
    if (a == 0) {
        if (total == n) return true;
        return false;
    }
    
    for (int i = b; i < n; ++i) {
        vector<bool> cz(n, false);
        int v = xx[i].v;
         if (!y[v]) {
             y[v] = true;

             if (!z[v]) {
                 cz[v] = true;
                 z[v] = true;
                 ++total;
             }
             for (int j = 0; j < x[v].size(); ++j)
              if (!z[x[v][j]]) {
                  z[x[v][j]] = true;
                  cz[x[v][j]] = true;
                  ++total;
              }
              
             if (dfs(a - 1, i + 1)) return true;
             
             for (int j = 0; j < n; ++j) {
                 if (!cz[j]) continue;
                 z[j] = false;
                 --total;
             }
             
             y[v] = false;
         }
    }
    
    return false;
}

int main() {
    int times = 0;
    while (cin >> n) {
        ++times;
        if (n == 0) break;
        memset(y, 0, sizeof(y));
        memset(z, 0, sizeof(z));
        total = 0;
        string p;
        for (int i = 0; i < n; ++i) {
            x[i].clear();
            xx[i].v = i;
            cin >> p;
            for (int j = 0; j < n; ++j) 
             if (p[j] == '1') x[i].push_back(j);
            xx[i].d = x[i].size();
        }
        
        sort(xx, xx+n, compare);
        
        for (int i = 1; i < 6; ++i) {
            if (dfs(i, 0)) {
                cout << "Case " << times << ": " << i;
                for (int j = 0; j < n; ++j) {
                    if (y[j]) cout << " " << j + 1;
                }
                cout << endl;
                break;
            }
        }
    }
    
    return 0;
}
