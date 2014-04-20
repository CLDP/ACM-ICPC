#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int PUT[8][4][3] = {0, 0, 0,  1, 0, 0,  1, 0, -1,  1, 0, -2,
                          0, 0, 0,  1, 0, 0,  1, 0, 1,   1, 0, 2,
                          0, 0, 0,  1, 0, 0,  1, 1, 0,   1, 2, 0,
                          0, 0, 0,  1, 0, 0,  1, -1, 0,  1, -2, 0,
                          0, 0, 0,  1, 0, 0,  2, 0, 0,   2, 0, 1, 
                          0, 0, 0,  1, 0, 0,  2, 0, 0,   2, 1, 0, 
                          0, 0, 0,  1, 0, 0,  2, 0, 0,   2, -1, 0, 
                          0, 0, 0,  1, 0, 0,  2, 0, 0,   2, 0, -1};

struct node {
    int x, y, z, dir;
};


const int FINAL[8][4] = {1, 0, -3, 5,  1, 0, 3, 4,  1, 3, 0, 2,  1, -3, 0, 3, 
                         2, 0, 2, 4,   2, 2, 0, 2,  2, -2, 0, 3, 2, 0, -2, 5};

int A, B, C;
node S, T;
bool z[22][22][22];

int change(node S, int &s1, int &s2, int &s3, int &p, int &q, int &r) {
    if (S.dir == 0) {
        s1 = 0, s2 = 1, s3 = 2;
        p = q = r = 1;
    } else
    if (S.dir == 1) {
        s1 = 0, s2 = 1, s3 = 2;
        p = -1, q = r = 1;
    } else 
    if (S.dir == 2) {
        s1 = 1, s2 = 0, s3 = 2;
        p = -1, q = r = 1;
    } else
    if (S.dir == 3) {
        s1 = 1, s2 = 0, s3 = 2;
        p = -1, q = -1, r = 1;
    } else
    if (S.dir == 4) {
        s1 = 2, s2 = 1, s3 = 0;
        r = 1, q = 1, p = -1;
    } else {
        s1 = 2, s2 = 1, s3 = 0;
        r = -1, q = 1, p = -1;
    }
    return 0;
}

bool check(node S, int t) {
    int s1, s2, s3, p, q, r;
    change(S, s1, s2, s3, p, q, r);
    for (int i = 0; i < 4; ++i) {
        int a = S.x + p * PUT[t][i][s1];
        int b = S.y + q * PUT[t][i][s2];
        int c = S.z + r * PUT[t][i][s3];
        if (a < 1 || a > A) return false;
        if (b < 1 || b > B) return false;
        if (c < 1 || c > C) return false;
        if (z[a][b][c]) return false;
    }
    return true;
}

int geton(node S, int t, bool flag) {
    int s1, s2, s3, p, q, r;
    change(S, s1, s2, s3, p, q, r);
    
    for (int i = 0; i < 4; ++i) {
        int a = S.x + p * PUT[t][i][s1];
        int b = S.y + q * PUT[t][i][s2];
        int c = S.z = r * PUT[t][i][s3];
        z[a][b][c] = flag;
    }
    return 0;
}


bool dfs(node S, int t) {
    if (t == 0) {
        if (S.x == T.x && S.y == T.y && S.z == T.z && S.dir == T.dir) return true;
        return false;
    }
    if (S.x < 1 || S.x > A || S.y < 1 || S.y > B || S.z < 1 || S.z > C) return false;
            
    int s[3], p[3];
    change(S, s[0], s[1], s[2], p[0], p[1], p[2]);
    
    for (int i = 0; i < 8; ++i) {
        if (check(S, i)) {
            geton(S, i, true);
            node next;
            next.x = S.x + FINAL[i][s[0]] * p[0];
            next.y = S.y + FINAL[i][s[1]] * p[1];
            next.z = S.z + FINAL[i][s[2]] * p[2];
            int dir = -1;
            for (int j = 0; j < 3; ++j)
             if (s[j] == FINAL[i][3] / 2) dir = j;
            next.dir = dir * 2 + (p[dir] > 0 ? FINAL[i][3] % 2 : (1 - FINAL[i][3] % 2));
            if (dfs(next, t - 1)) return true;
            geton(S, i, false);
        }
    }
    return false;
}


int main() {
    int times = 0;
    while (cin >> A >> B >> C) {
        if (A == 0) break;
        string P;
        cin >> S.x >> S.y >> S.z >> P;
        S.dir = (P[1] - 'x') * 2 + (P[0] == '+' ? 0 : 1);
        cin >> T.x >> T.y >> T.z >> P;
        T.dir = (P[1] - 'x') * 2 + (P[0] == '+' ? 0 : 1);
        switch (T.dir) {
            case 0 : ++T.x; break;
            case 1 : --T.x; break;
            case 2 : ++T.y; break;
            case 3 : --T.y; break;
            case 4 : ++T.z; break;
            case 5 : --T.z; break;
        }
        
        bool flag = false;
        memset(z, 0, sizeof(z));
        for (int i = 1; i <= 6; ++i) {
            if (dfs(S, i)) {
                cout << "Case " << ++times << ": " << i << endl;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "Case " << ++times << ": Impossible" << endl;
        }
    }
    return 0;
}
