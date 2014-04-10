#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

string P[16][15];
int L[16], R[16], U[16], D[16];
bool X[16][4];
char x[100][100];
bool z[20];
int k, w, h, n;


int puton(int Bx, int By, int t) {
    for (int i = 0; i < 3 * h - 2; ++i)
     for (int j = 0; j < 3 * w - 2; ++j) {
         if (P[t][i][j] == '.') continue;
         x[i - Bx][j - By] = P[t][i][j];
     }
    return 0;
}

bool checkput(int Bx, int By, int t) {
    for (int i = 0; i < 3 * h - 2; ++i)
     for (int j = 0; j < 3 * w - 2; ++j) {
         if (P[t][i][j] == '.') continue;
         if (x[i - Bx][j - By] != '.') return false;
     }
    return true;
}

int takeoff(int Bx, int By, int t) {
    for (int i = 0; i < 3 * h - 2; ++i)
     for (int j = 0; j < 3 * w - 2; ++j) {
         if (P[t][i][j] == '.') continue;
         x[i - Bx][j - By] = '.';
     }
    return 0;
}


bool dfs(int a) {
    vector<int> Y;
    if (a < 4) {
        for (int t = 0; t < k; ++t) 
         if (!z[t] && X[t][a]) Y.push_back(t);
     }
     
    int Bx1, By1, Bx2, By2;
    if (a == 0) {
        Bx1 = - h, By1 = 0, Bx2 = - h - h, By2 = 0;
    }
    if (a == 1) {
        Bx1 = - h - h - h, By1 = - w, Bx2 = - h - h - h, By2 = - w - w;
    }
    if (a == 2) {
        Bx1 = - h - h, By1 = - w - w - w, Bx2 = - h, By2 = - w - w - w;
    }
    if (a == 3) {
        Bx1 = 0, By1 = - w, Bx2 = 0, By2 = - w - w;
    }
    if (a < 4) {
        z[Y[0]] = z[Y[1]] = true;
        if (checkput(h - 1 + Bx1, w - 1 + By1, Y[0])) {
            puton(h - 1 + Bx1, w - 1 + By1, Y[0]);
            if (checkput(h - 1 + Bx2, w - 1 + By2, Y[1])) {
                puton(h - 1 + Bx2, w - 1 + By2, Y[1]);
                if (dfs(a + 1)) return true;
                takeoff(h - 1 + Bx2, w - 1 + By2, Y[1]);
            }
            takeoff(h - 1 + Bx1, w - 1 + By1, Y[0]);
        }
        swap(Y[0], Y[1]);
        if (checkput(h - 1 + Bx1, w - 1 + By1, Y[0])) {
            puton(h - 1 + Bx1, w - 1 + By1, Y[0]);
            if (checkput(h - 1 + Bx2, w - 1 + By2, Y[1])) {
                puton(h - 1 + Bx2, w - 1 + By2, Y[1]);
                if (dfs(a + 1)) return true;
                takeoff(h - 1 + Bx2, w - 1 + By2, Y[1]);
            }
            takeoff(h - 1 + Bx1, w - 1 + By1, Y[0]);
        }
        z[Y[0]] = z[Y[1]] = false;
        return false;
    }
    
    for (int i = 0; i < k; ++i)
     if (!z[i]) Y.push_back(i);
    
    do {
        if (checkput(h - 1 - h, w - 1 - w, Y[0])) {
            puton(h - 1 - h, w - 1 - w, Y[0]);
            if (checkput(h - 1 - h - h, w - 1 - w, Y[1])) {
                puton(h - 1 - h - h, w - 1 - w, Y[1]);
                if (checkput(h - 1 - h, w - 1 - w - w, Y[2])) {
                    puton(h - 1 - h, w - 1 - w - w, Y[2]);
                    if (checkput(h - 1 - h - h, w - 1 - w - w, Y[3])) {
                        puton(h - 1 - h - h, w - 1 - w - w, Y[3]);
                        return true;
                    }
                    takeoff(h - 1 - h, w - 1 - w - w, Y[2]);
                }
                takeoff(h - 1 - h - h, w - 1 - w, Y[1]);
            }
            takeoff(h - 1 - h, w - 1 - w, Y[0]);
        }
    } while (next_permutation(Y.begin(), Y.end()));
    
    return false;
}

int main() {
    freopen("ascii.in", "r", stdin);
    freopen("ascii.out", "w", stdout);
    cin >> k >> w >> h;
    n = sqrt(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < 3 * h - 2; ++j) cin >> P[i][j];
        
        L[i] = U[i] = 100;
        R[i] = D[i] = 0;
        for (int p = 0; p < 3 * h - 2; ++p)
         for (int q = 0; q < 3 * w - 2; ++q) {
             if (P[i][p][q] == '.') continue;
             L[i] = min(L[i], q);
             U[i] = min(U[i], p);
             R[i] = max(R[i], q);
             D[i] = max(D[i], p);
         }
        
        if (L[i] == w - 1) {
            bool flag = true;
            for (int p = h - 1; p < h - 1 + h; ++p) 
                flag &= (P[i][p][L[i]] != '.');
            if (flag) X[i][0] = true;
        }
        
        if (R[i] == w - 1 + w - 1) {
            bool flag = true;
            for (int p = h - 1; p < h - 1 + h; ++p) 
                flag &= (P[i][p][R[i]] != '.');
            if (flag) X[i][2] = true;
        }
        
        if (D[i] == h - 1 + h - 1) {
            bool flag = true;
            for (int q = w - 1; q < w - 1 + w; ++q) 
                flag &= (P[i][D[i]][q] != '.');
            if (flag) X[i][1] = true;
        }
        
        if (U[i] == h - 1) {
            bool flag = true;
            for (int q = w - 1; q < w - 1 + w; ++q) 
                flag &= (P[i][U[i]][q] != '.');
            if (flag) X[i][3] = true;
        }
    }
    
    if (k == 1) {
        cout << w << " " << h << endl;
        for (int i = h - 1; i < h + h - 1; ++i) {
            for (int j = w - 1; j < w + w - 1; ++j) cout << P[0][i][j];
            cout << endl;
        }
        return 0;
    }
    
    for (int i = 0; i < h * n; ++i)
     for (int j = 0; j < w * n; ++j) x[i][j] = '.';
    
    for (int t = 0; t < k; ++t) {
        if (X[t][0] && X[t][3]) {
            z[t] = true;
            puton(h - 1, w - 1, t);
        }
        if (X[t][0] && X[t][1]) {
            z[t] = true;
            puton(h - 1 - h * (n - 1), w - 1, t);
        }
        if (X[t][2] && X[t][1]) {
            z[t] = true;
            puton(h - 1 - h * (n - 1), w - 1 - w * (n - 1), t);
        }
        if (X[t][2] && X[t][3]) {
            z[t] = true;
            puton(h - 1, w - 1 - w * (n - 1), t);
        }
    }
    
    if (n == 2) {
    
    } else
    if (n == 3) {
        for (int t = 0; t < k; ++t) {
            if (z[t]) continue;
            if (X[t][0]) {
                z[t] = true;
                puton(h - 1 - h, w - 1, t);
            }
            if (X[t][1]) {
                z[t] = true;
                puton(h - 1 - h - h, w - 1 - w, t);
            }
            if (X[t][2]) {
                z[t] = true;
                puton(h - 1 - h, w - 1 - w - w, t);
            }
            if (X[t][3]) {
                z[t] = true;
                puton(h - 1, w - 1 - w, t);
            }
        }
        for (int t = 0; t < k; ++t) {
            if (z[t]) continue;
            puton(h - 1 - h, w - 1 - w, t);
            break;
        }
    } else {
        dfs(0);
    }
    
    cout << w * n << " " << h * n << endl;
    for (int i = 0; i < h * n; ++i) {
        for (int j = 0; j < w * n; ++j) cout << x[i][j];
        cout << endl;
    }
    
    return 0;
}
