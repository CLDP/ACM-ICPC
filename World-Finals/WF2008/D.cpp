#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 200;

struct road1 {
    int a, b, d1, d2, l;
    bool mark;
    int D;
};

struct road2 {
    int v, d1, d2, l, id;
    bool done;
    road2(int _v, int _d1, int _d2, int _l, int _id) : v(_v), d1(_d1), d2(_d2), l(_l), id(_id) {}
};

int ncp, nroad, ncm, confdist, ss, es, sd;
bool cp[MAXN];
road1 X[MAXN];
vector<road2> x[MAXN];
int ans1, ans2, temp;
vector<int> ansD;


bool cansee(int ID, int a, int left) {
    if (a == X[ID].a) {
        return X[ID].D <= left;
    } else {
        return X[ID].l - X[ID].D <= left;
    }
}

bool better(int d1, int d2, int D) {
    // return true is d1 is better
    if (D - d1 > 180) d1 += 360;
    if (d1 - D > 180) d1 -= 360;
    if (D - d2 > 180) d2 += 360;
    if (d2 - D > 180) d2 -= 360;
    int df1 = D - d1, df2 = D - d2;
    if (abs(df1) != abs(df2)) return abs(df1) < abs(df2);
    return df1 < 0;
}

bool dfs(int a, int dir, int search, int L, int prev) {
    if (search == 0) {
        if (a == es) return true;
        int t = 0;
        // should never go back
        for (int i = 1; i < x[a].size(); ++i) {
            if (better(x[a][i].d1, x[a][t].d1, (dir + 180) % 360)) t = i;
        }
        ans1 += x[a][t].l;
        ansD.push_back(x[a][t].id);
        if (cp[x[a][t].v]) {
            int aa = x[a][t].v;
            for (int i = 0; i < x[aa].size(); ++i) x[aa][i].done = false;
        }
        dfs(x[a][t].v, x[a][t].d2, cp[x[a][t].v], 0, x[a][t].id);
    } else 
    if (search == 1) {
        for (int i = 0; i < x[a].size(); ++i)
         if (x[a][i].id == prev && dir == x[a][i].d1) x[a][i].done = true;
        
        int t = -1;
        for (int i = 0; i < x[a].size(); ++i) {
            if (!x[a][i].done && (t == -1 || better(x[a][i].d1, x[a][t].d1, (dir + 180) % 360))) t = i;
        }
        x[a][t].done = true;
        ansD.push_back(x[a][t].id);
        if (X[x[a][t].id].mark && cansee(x[a][t].id, a, confdist - L)) {
            dfs(x[a][t].v, x[a][t].d2, cp[x[a][t].v], 0, x[a][t].id);
            ans1 += x[a][t].l;
        } else 
        if (x[a][t].l >= confdist - L) {
            ans2 += (confdist - L) * 2;
            ansD.erase(ansD.end() - 1);
            dfs(a, x[a][t].d1, 1, 0, x[a][t].id);
        } else 
        if (cp[x[a][t].v]) {
            ans2 += x[a][t].l * 2;
            ansD.erase(ansD.end() - 1);
            dfs(a, x[a][t].d1, 1, 0, x[a][t].id);
        } else {
            temp = x[a][t].l;
            if (!dfs(x[a][t].v, x[a][t].d2, 2, x[a][t].l, x[a][t].id)) {
                ans2 += temp + x[a][t].l;
                temp = 0;
                ansD.erase(ansD.end() - 1);
                dfs(a, x[a][t].d1, 1, 0, x[a][t].id);
            }
        }
    } else {
        int t = 0;
        // should never go back
        for (int i = 1; i < x[a].size(); ++i)
         if (better(x[a][i].d1, x[a][t].d1, (dir + 180) % 360)) t = i;
        ansD.push_back(x[a][t].id);
        if (X[x[a][t].id].mark && cansee(x[a][t].id, a, confdist - L)) {
            ans1 += temp + x[a][t].l;
            dfs(x[a][t].v, x[a][t].d2, cp[x[a][t].v], 0, x[a][t].id);
        } else 
        if (x[a][t].l >= confdist - L) {
            ansD.erase(ansD.end() - 1);
            temp += (confdist - L) * 2;
            return false;
        } else
        if (cp[x[a][t].v]) {
            temp += x[a][t].l * 2;
            ansD.erase(ansD.end() - 1);
            return false;
        } else {
            temp += x[a][t].l;
            if (!dfs(x[a][t].v, x[a][t].d2, 2, L + x[a][t].l, x[a][t].id)) {
                temp += x[a][t].l;
                ansD.erase(ansD.end() - 1);
                return false;
            }
        }
    }
    return true;
}


int main() {
    int times = 0;
    while (cin >> ncp >> nroad >> ncm >> confdist >> ss >> es >> sd) {
        if (nroad == 0) break;
        memset(cp, 0, sizeof(cp));
        for (int i = 0; i < ncp; ++i) {
            int a;
            cin >> a;
            cp[a] = true;
        }
        for (int i = 1; i <= 100; ++i) x[i].clear();
        for (int i = 1; i <= nroad; ++i) {
            cin >> X[i].a >> X[i].b >> X[i].d1 >> X[i].d2 >> X[i].l;
            x[X[i].a].push_back(road2(X[i].b, X[i].d1, X[i].d2, X[i].l, i));
            x[X[i].b].push_back(road2(X[i].a, X[i].d2, X[i].d1, X[i].l, i));
            X[i].mark = false;
        }
        for (int i = 0; i < ncm; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            X[b].mark = true;
            if (a == X[b].a) X[b].D = c; else X[b].D = X[b].l - c;
        }
        
        ans1 = ans2 = 0;
        ansD.clear();
        dfs(ss, (sd + 180) % 360, false, 0, -1);
        cout << "Case " << ++times << ":" << endl;
        cout << "   Length of hare's route is " << ans1 << endl;
        cout << "   Length of hound's search is " << ans1 + ans2 << endl;
        cout << "   Route:";
        for (int i = 0; i < ansD.size(); ++i) cout << " " << ansD[i];
        cout << endl << endl;
    }
    return 0;
}
