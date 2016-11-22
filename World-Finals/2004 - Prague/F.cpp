#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct seg {
    int r, c, seq;
    vector<string> X;
};


int cal(const seg &A, const seg &B, int &px, int &py) {
    int ans = 0;
    for (int i = - (B.r - 1); i <= A.r - 1; ++i)
     for (int j = - (B.c - 1); j <= A.c - 1; ++j) {
         int temp = 0;
         for (int p = 0; p < A.r; ++p)
          for (int q = 0; q < A.c; ++q) {
              if (!(0 <= p - i && p - i < B.r && 0 <= q - j && q - j < B.c)) continue;
              if (A.X[p][q] == '-' || B.X[p - i][q - j] == '-') continue;
              if (A.X[p][q] == B.X[p - i][q - j]) ++temp; else temp = -INF;
          }
         if (temp > ans) ans = temp, px = i, py = j;
     }
    return ans;
}

seg mergeX(const seg &A, const seg &B, int px, int py, int seq) {
    seg C;
    C.seq = seq;
    C.r = max(B.r + px, A.r) - min(0, px);
    C.c = max(B.c + py, A.c) - min(0, py);
    C.X.push_back("");
    for (int i = 0; i < C.c; ++i) C.X[0] = C.X[0] + "-";
    for (int i = 1; i < C.r; ++i) C.X.push_back(C.X[0]);
    
    int Ar = 0, Ac = 0, Br = 0, Bc = 0;
    if (px < 0) Ar = -px; else Br = px;
    if (py < 0) Ac = -py; else Bc = py;
    
    for (int i = 0; i < A.r; ++i)
     for (int j = 0; j < A.c; ++j) 
      if (A.X[i][j] != '-') C.X[i + Ar][j + Ac] = A.X[i][j];
    for (int i = 0; i < B.r; ++i)
     for (int j = 0; j < B.c; ++j) 
      if (B.X[i][j] != '-') C.X[i + Br][j + Bc] = B.X[i][j];
    
    return C;
}

int print(const seg &C) {
    cout << "    +";
    for (int j = 0; j < C.c; ++j) cout << "-";
    cout << "+" << endl;
    for (int j = 0; j < C.r; ++j) {
        cout << "    |" << C.X[j] << "|" << endl;
    }
    cout << "    +";
    for (int j = 0; j < C.c; ++j) cout << "-";
    cout << "+" << endl;
    return 0;
}


int main() {
    int N, times = 0;
    bool first = true;
    while (cin >> N) {
        if (N == 0) break;
        if (!first) cout << endl;
        first = false;
        
        vector<seg> x(N);
        string trash;
        for (int i = 0; i < N; ++i) {
            x[i].seq = i + 1;
            cin >> x[i].r >> x[i].c;
            getline(cin, trash);
            x[i].X = vector<string> (x[i].r);
            for (int j = 0; j < x[i].r; ++j) {
                getline(cin, trash);
                x[i].X[j] = trash.substr(0, x[i].c);
            }
        }
        
        for (int k = 1; k < N; ++k) {
            int ans = 0, a, b, c, d;
            for (int i = 0; i < x.size(); ++i) 
             for (int j = i + 1; j < x.size(); ++j) {
                 int temp, p, q;
                 temp = cal(x[i], x[j], p, q);
                 if (temp > ans) ans = temp, a = i, b = j, c = p, d = q;
             }
            if (ans == 0) break;
            x.push_back(mergeX(x[a], x[b], c, d, N + k));
            x.erase(x.begin() + b);
            x.erase(x.begin() + a);
        }
        
        cout << "Case " << ++times << endl;
        for (int i = 0; i < x.size(); ++i) {
            cout << "    MAP " << x[i].seq << ":" << endl;
            print(x[i]);
            if (i != x.size() - 1) cout << endl;
        }
    }
    return 0;
}
