#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;


struct node {
    long double x[3], v[3];
};

struct change{
    long double t;
    int a, b, c, d;
    
    change(long double t1, int a1, int b1, int c1, int d1)
        : t(t1), a(a1), b(b1), c(c1), d(d1) {}
    
    bool operator < (change const &B) const {
        return t < B.t;
    }
};

vector<node> X;
vector<change> T;


long double dist(int a, int b, long double time) {
    long double ans = 0;
    for (int j = 0; j < 3; ++j) {
        long double temp = (X[a].x[j] + X[a].v[j] * time - X[b].x[j] - X[b].v[j] * time);
        ans += temp * temp;
    }
    return ans;
}


int solve(int a, int b, int c, int d, long double &L, long double &R) {
    long double A = 0, B = 0, C = 0;
    for (int i = 0; i < 3; ++i) {
        A += (X[a].v[i] - X[b].v[i]) * (X[a].v[i] - X[b].v[i]);
        A -= (X[c].v[i] - X[d].v[i]) * (X[c].v[i] - X[d].v[i]);
        B += 2 * (X[a].x[i] - X[b].x[i]) * (X[a].v[i] - X[b].v[i]);
        B -= 2 * (X[c].x[i] - X[d].x[i]) * (X[c].v[i] - X[d].v[i]);
        C += (X[a].x[i] - X[b].x[i]) * (X[a].x[i] - X[b].x[i]);
        C -= (X[c].x[i] - X[d].x[i]) * (X[c].x[i] - X[d].x[i]);
    }
    if (A == 0) {
        if (B == 0) 
            L = R = -1;
        else 
            L = R = - C / B;
        return 0;
    }
    if (B * B - 4 * A * C < 0) {
        L = R = -1;
        return 0;
    }
    L = (- B + sqrt(B * B - 4 * A * C)) / (2 * A);
    R = (- B - sqrt(B * B - 4 * A * C)) / (2 * A);
    return 0;
}

int check(int a, int b, int c, int d) {
    long double L, R;
    solve(a, b, c, d, L, R);
    if (L > 0) T.push_back(change(L, a, b, c, d));
    if (fabs(L - R) > 1e-8 && R > 0) T.push_back(change(R, a, b, c, d));
    return 0;
}

int prim(int N, set<pair<int, int> > &tree, long double time) {
    vector<long double> D(N + 1, 1e100);
    vector<bool> z(N + 1, false);
    vector<int> F(N + 1, 0);
    
    D[0] = 0;
    z[0] = true;
    for (int i = 1; i < N; ++i) D[i] = dist(0, i, time);
    
    for (int i = 0; i < N; ++i) {
        long double minD = 1e100;
        int temp = 0;
        for (int j = 0; j < N; ++j) 
         if (!z[j] && D[j] < minD) {
             temp = j;
             minD = D[j];
         }
        
        if (temp == 0) break;
        z[temp] = true;
        tree.insert(make_pair(min(temp, F[temp]), max(temp, F[temp])));
        for (int j = 0; j < N; ++j) {
            long double tempD = dist(j, temp, time);
            if (tempD < D[j]) {
                D[j] = tempD;
                F[j] = temp;
            }
        }
    }
    
    return 0;
}


bool change_seg(set<pair<int, int> > &tree, int N, long double time) {
    set<pair<int, int> > new_tree;
    prim(N, new_tree, time);
    
    set<pair<int, int> >::iterator iter1 = tree.begin(), iter2 = new_tree.begin();
    while (iter1 != tree.end()) {
        if (*iter1 != *iter2) {
            tree = new_tree;
            return true;
        }
        ++iter1;
        ++iter2;
    }
    
    return false;
}


int main() {
    int N, TT = 0;
    while (cin >> N) {
        ++TT;
        X.clear();
        for (int i = 0; i < N; ++i) {
            node p;
            for (int j = 0; j < 3; ++j) cin >> p.x[j];
            for (int j = 0; j < 3; ++j) cin >> p.v[j];
            X.push_back(p);
        }
        
        T.clear();
        T.push_back(change(0, 0, 0, 0, 0));
        for (int i = 0; i < N; ++i)
         for (int j = i + 1; j < N; ++j)
          for (int k = i; k < N; ++k)
           for (int l = k + 1; l < N; ++l) {
               if (i == k && j >= l) continue;
               check(i, j, k, l);
           }
        
        sort(T.begin(), T.end());
        set<pair<int, int> > tree;
        
        prim(N, tree, 0);
        
        int ans = 1;
        double prev = 0;
        for (int i = 1; i < T.size(); ++i) {
            bool find1 = tree.find(make_pair(T[i].a, T[i].b)) != tree.end();
            bool find2 = tree.find(make_pair(T[i].c, T[i].d)) != tree.end();
            if (find1 == find2) continue;
            if (change_seg(tree, N, T[i].t + 0.5 * 1e-6)) ++ans;
        }
        
        cout << "Case " << TT << ": " << ans << endl;
    }
    
    return 0;
}
