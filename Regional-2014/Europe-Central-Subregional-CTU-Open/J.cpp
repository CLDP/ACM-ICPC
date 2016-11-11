#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct node {
    int a, b;
    int da, db;
    node(int _a, int _b, int _da, int _db) {
        a = _a;
        b = _b;
        da = _da;
        db = _db;
        if (da < 0 || (da == 0 && db < 0)) {
            a += da;
            b += db;
            da = -da;
            db = -db;
        }
    }
    
    bool operator < (node const C) const {
        if (db == 0 && C.db != 0) return true;
        if (db != 0 && C.db == 0) return false;
        if (db == 0) {
            if (b != C.b) return b < C.b;
            return a < C.a;
        }
        if (db * C.da != da * C.db) return db * C.da < da * C.db;
        if (da == 0) {
            if (a != C.a) return a < C.a;
            return b < C.b;
        }
        if (1LL * a * db * C.db - 1LL * b * da * C.db != 1LL * C.a * db * C.db - 1LL * C.b * db * C.da) 
            return 1LL * a * db * C.db - 1LL * b * da * C.db < 1LL * C.a * db * C.db - 1LL * C.b * db * C.da;
        if (a != C.a) return a < C.a;
        return b < C.b;
    }
};


bool sameL(const node &A, const node &B) {
    if (A.db == 0 && B.db != 0) return false;
    if (A.db != 0 && B.db == 0) return false;
    if (A.db == 0) return A.b == B.b;
    if (A.db * B.da != A.da * B.db) return false;
    if (A.da == 0) return A.a == B.a;
    
    return 1LL * A.a * A.db * B.db - 1LL * A.b * A.da * B.db == 1LL * B.a * A.db * B.db - 1LL * B.b * A.db * B.da;
}


vector<node> X, Y;


int main() {
    int N, M;
    while (cin >> N) {
        X.clear();
        Y.clear();
        
        int minx1 = INF, miny1 = INF, minx2 = INF, miny2 = INF;
        
        string P;
        int a, b;
        int A = 0, B = 0;
        for (int i = 0; i < N; ++i) {
            cin >> P >> a >> b;
            if (P == "L") {
                X.push_back(node(A, B, a, b));
                if (A < minx1 || (A == minx1 && B < miny1)) {
                    minx1 = A;
                    miny1 = B;
                } 
                if (A + a < minx1 || (A + a == minx1 && B + b < miny1)) {
                    minx1 = A + a;
                    miny1 = B + b;
                } 
            }
            A += a;
            B += b;
        }
        
        cin >> M;
        A = B = 0;
        for (int i = 0; i < M; ++i) {
            cin >> P >> a >> b;
            if (P == "L") {
                Y.push_back(node(A, B, a, b));
                if (A < minx2 || (A == minx2 && B < miny2)) {
                    minx2 = A;
                    miny2 = B;
                } 
                if (A + a < minx2 || (A + a == minx2 && B + b < miny2)) {
                    minx2 = A + a;
                    miny2 = B + b;
                } 
            }
            A += a;
            B += b;
        }
        
        for (int i = 0; i < Y.size(); ++i) {
            Y[i].a += minx1 - minx2;
            Y[i].b += miny1 - miny2;
        }
        sort(X.begin(), X.end());
        
        sort(Y.begin(), Y.end());
        bool flag = true;
        N = X.size(), M = Y.size();
        int i = 0, j = 0;
        while (i < N && j < M) {
            int k = i, l = j;
            if (i == N || j == M) {
                flag = false;
                break;
            }
            if (!sameL(X[i], Y[j])) {
                flag = false;
                break;
            }
            while (k < N && sameL(X[i], X[k])) ++k;
            while (l < M && sameL(Y[j], Y[l])) ++l;
            
            if (X[i].da == 0) {
                // only consider .b
                while (i < k || j < l) {
                    if (i == k || j == l) {
                        flag = false;
                        break;
                    }
                    int A = X[i].b, B = X[i].b + X[i].db;
                    int C = Y[j].b, D = Y[j].b + Y[j].db;
                    while (i < k) {
                        if (A <= X[i].b && X[i].b <= B) B = max(X[i].b + X[i].db, B);
                        ++i;
                    }
                    while (j < l) {
                        if (C <= Y[j].b && Y[j].b <= D) D = max(Y[j].b + Y[j].db, D);
                        ++j;
                    }
                    if (A != C || B != D) {
                        flag = false;
                        break;
                    }
                }
            } else {
                // only consider .a
                while (i < k || j < l) {
                    if (i == k || j == l) {
                        flag = false;
                        break;
                    }
                    int A = X[i].a, B = X[i].a + X[i].da;
                    int C = Y[j].a, D = Y[j].a + Y[j].da;
                    while (i < k) {
                        if (A <= X[i].a && X[i].a <= B) B = max(X[i].a + X[i].da, B);
                        ++i;
                    }
                    while (j < l) {
                        if (C <= Y[j].a && Y[j].a <= D) D = max(Y[j].a + Y[j].da, D);
                        ++j;
                    }
                    if (A != C || B != D) {
                        flag = false;
                        break;
                    }
                }
            }
        }
        
        if (flag) cout << "YES" << endl; else cout << "NO" << endl;
    }
    return 0;
}
