#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 2011;
const int INF = 1000000000;


struct triangle {
    double l[3], d[3];
};


int n, m;
vector<triangle> big, small;
vector<pair<int, int> > can[21];
bool x[41][41][21], z[41];
int ans[21][2];

bool same(double a, double b) {
    return fabs(a - b) < 0.01;
}

bool checkS(int a, int b, int c) {
    if (same(small[a].l[0], big[c].l[0])
     && same(small[b].l[0], big[c].l[1]) 
     && same(small[a].l[2] + small[b].l[1], big[c].l[2])
     && same(small[a].d[1], big[c].d[1])
     && same(small[b].d[2], big[c].d[0])) return true;
    
    return false;
}

int changeT(int a, bool bigS) {
    if (bigS) {
        double temp = big[a].l[0];
        big[a].l[0] = big[a].l[1];
        big[a].l[1] = big[a].l[2];
        big[a].l[2] = temp;
        temp = big[a].d[0];
        big[a].d[0] = big[a].d[1];
        big[a].d[1] = big[a].d[2];
        big[a].d[2] = temp;
    } else {
        double   temp = small[a].l[0];
        small[a].l[0] = small[a].l[1];
        small[a].l[1] = small[a].l[2];
        small[a].l[2] = temp;
        temp = small[a].d[0];
        small[a].d[0] = small[a].d[1];
        small[a].d[1] = small[a].d[2];
        small[a].d[2] = temp;
    }
    
    return 0;
}


bool check(int a, int b, int c) {
    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (checkS(a, b, c)) return true;
                changeT(b, false);
            }
            changeT(a, false);
        }
        changeT(c, true);
    }
    return false;
}

bool dfs(int a) {
    if (n == a) return true;
    
    for (int i = 0; i < can[a].size(); ++i) {
        if (!z[can[a][i].first] && !z[can[a][i].second]) {
            z[can[a][i].first] = true;
            z[can[a][i].second] = true;
            ans[a][0] = can[a][i].first;
            ans[a][1] = can[a][i].second;
            if (dfs(a + 1)) return true;
            z[can[a][i].first] = false;
            z[can[a][i].second] = false;
        }
    }
    
    return false;
}


int main() {
    int times = 0;
    while (cin >> n) {
        if (n == 0) break;
        if (times > 0) cout << endl;
        ++times;
        big.clear();
        small.clear();
        memset(x, 0, sizeof(x));
        
        for (int i = 0; i < n; ++i) {
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            triangle nt;
            nt.l[0] = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            nt.l[1] = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
            nt.l[2] = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
            nt.d[0] = (nt.l[1] * nt.l[1] + nt.l[2] * nt.l[2] - nt.l[0] * nt.l[0]) / (2 * nt.l[1] * nt.l[2]);
            nt.d[1] = (nt.l[0] * nt.l[0] + nt.l[2] * nt.l[2] - nt.l[1] * nt.l[1]) / (2 * nt.l[0] * nt.l[2]);
            nt.d[2] = (nt.l[1] * nt.l[1] + nt.l[0] * nt.l[0] - nt.l[2] * nt.l[2]) / (2 * nt.l[1] * nt.l[0]);
            big.push_back(nt);
        }
        
        for (int i = 0; i < 2 * n; ++i) {
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            triangle nt;
            nt.l[0] = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            nt.l[1] = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
            nt.l[2] = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
            nt.d[0] = (nt.l[1] * nt.l[1] + nt.l[2] * nt.l[2] - nt.l[0] * nt.l[0]) / (2 * nt.l[1] * nt.l[2]);
            nt.d[1] = (nt.l[0] * nt.l[0] + nt.l[2] * nt.l[2] - nt.l[1] * nt.l[1]) / (2 * nt.l[0] * nt.l[2]);
            nt.d[2] = (nt.l[1] * nt.l[1] + nt.l[0] * nt.l[0] - nt.l[2] * nt.l[2]) / (2 * nt.l[1] * nt.l[0]);
            small.push_back(nt);
        }
        
        memset(x, 0, sizeof(x));
        for (int i = 0; i < n; ++i) can[i].clear();
        
        for (int i = 0; i < 2 * n; ++i)
         for (int j = 0; j < 2 * n; ++j) 
          if (i != j)
           for (int k = 0; k < n; ++k) 
            if (check(i, j, k)) {
                if (i < j)
                    can[k].push_back(make_pair(i, j));
                else
                    can[k].push_back(make_pair(j, i));
            }
        
        cout << "Case " << times << ":" << endl;
        
        memset(z, 0, sizeof(z));
        dfs(0);
        
        for (int i = 0; i < n; ++i) {
            cout << "Hole " << i + 1 << ": " << ans[i][0] + 1 << ", " << ans[i][1] + 1 << endl;
        }
    }

    return 0;
}
