#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct node {
    char c1, c2;
    int t;
};

node f[10005][10005];

int main() {
    int n, r1, c1, ind1, r2, c2, ind2, rf, cf;
    char m[105][105];
    
    int times;
    cin >> times;
    while (times) {
        cin >> n;
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j) cin >> m[i][j];
        
        vector<int> q;
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j) {
             ind1 = i * n + j;
             f[ind1][ind1].t = times;
             q.push_back(ind1 * 10000 + ind1);
         }
        
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j) {
             ind1 = i * n + j;
             if (j < n - 1) {
                 if (m[i][j] == m[i][j+1]) {
                     ind2 = ind1 + 1;
                     f[ind1][ind2].t = times;
                     q.push_back(ind1 * 10000 + ind2);
                 }
             }
             if (i < n - 1) {
                 if (m[i][j] == m[i+1][j]) {
                     ind2 = ind1 + n;
                     f[ind1][ind2].t = times;
                     q.push_back(ind1 * 10000 + ind2);
                 }
             }
         }
        
        unsigned int p = 0;
        while (p < q.size()) {
            ind1 = q[p] / 10000;
            ind2 = q[p] % 10000;
            r1 = ind1 / n;
            c1 = ind1 % n;
            r2 = ind2 / n;
            c2 = ind2 % n;
            
            if ((r1 > 0) && (r2 < n - 1)) {
                if ((m[r1 - 1][c1] == m[r2 + 1][c2]) && (f[ind1 - n][ind2 + n].t != times)) {
                    f[ind1 - n][ind2 + n].t = times;
                    q.push_back((ind1 - n) * 10000 + ind2 + n);
                    f[ind1 - n][ind2 + n].c1 = 'D';
                    f[ind1 - n][ind2 + n].c2 = 'D';
                }
            }
            
            if ((r1 > 0) && (c2 < n - 1)) {
                if ((m[r1 - 1][c1] == m[r2][c2 + 1]) && (f[ind1 - n][ind2 + 1].t != times)) {
                    f[ind1 - n][ind2 + 1].t = times;
                    q.push_back((ind1 - n) * 10000 + ind2 + 1);
                    f[ind1 - n][ind2 + 1].c1 = 'D';
                    f[ind1 - n][ind2 + 1].c2 = 'R';
                }
            }
            
            if ((c1 > 0) && (r2 < n - 1)) {
                if ((m[r1][c1 - 1] == m[r2 + 1][c2]) && (f[ind1 - 1][ind2 + n].t != times)) {
                    f[ind1 - 1][ind2 + n].t = times;
                    q.push_back((ind1 - 1) * 10000 + ind2 + n);
                    f[ind1 - 1][ind2 + n].c1 = 'R';
                    f[ind1 - 1][ind2 + n].c2 = 'D';
                }
            }
            
            if ((c1 > 0) && (c2 < n - 1)) {
                if ((m[r1][c1 - 1] == m[r2][c2 + 1]) && (f[ind1 - 1][ind2 + 1].t != times)) {
                    f[ind1 - 1][ind2 + 1].t = times;
                    q.push_back((ind1 - 1) * 10000 + ind2 + 1);
                    f[ind1 - 1][ind2 + 1].c1 = 'R';
                    f[ind1 - 1][ind2 + 1].c2 = 'R';
                }
            }
            ++p;
        }
        
        p--;
        string s1 = "", s2 = "S", s3 = "", s4 = "";
        ind1 = q[p] / 10000;
        ind2 = q[p] % 10000;
        r1 = ind1 / n;
        c1 = ind1 % n;
        r2 = ind2 / n;
        c2 = ind2 % n;
        
        rf = r1;
        cf = c1;
        
        while (r2 + c2 - r1 - c1 > 1) {
            s1 = s1 + f[ind1][ind2].c1;
            s2 = f[ind1][ind2].c2 + s2;
            s3 = s3 + m[r1][c1];
            s4 = m[r2][c2] + s4;
            if (f[ind1][ind2].c1 == 'D') r1++; else c1++;
            if (f[ind1][ind2].c2 == 'D') r2--; else c2--;
            ind1 = r1 * n + c1;
            ind2 = r2 * n + c2;
        }
        
        if (r2 == r1 + 1) {
            s1 = s1 + 'D' + s2;
            s3 = s3 + m[r1][c1];
            s4 = m[r2][c2] + s4;
        } else 
        if (c2 == c1 + 1) {
            s1 = s1 + 'R' + s2;
            s3 = s3 + m[r1][c1];
            s4 = m[r2][c2] + s4;
        } else {
            s1 = s1 + s2;
            s3 = s3 + m[r1][c1];
        }
        
        cout << s3 << s4 << " " << rf + 1 << " " << cf + 1 << " " << s1 << endl;
        
        --times;
    }

    return 0;
}
