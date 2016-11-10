#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string S[3];

int change(char &P) {
    if (P == '*') P = '.'; else P = '*';
    return 0;
}

bool doit(int A) {
    string P[3];
    P[0] = S[0], P[1] = S[1], P[2] = S[2];
    for (int i = 0; i < 9; ++i) {
        if (A & (1 << i)) {
            int a = i / 3, b = i % 3;
            change(P[a][b]);
            if (a > 0) change(P[a - 1][b]);
            if (b > 0) change(P[a][b - 1]);
            if (a < 2) change(P[a + 1][b]);
            if (b < 2) change(P[a][b + 1]);
        }
    }
    for (int i = 0; i < 3; ++i)
     for (int j = 0; j < 3; ++j) 
      if (P[i][j] == '*') return false;
    return true;
}

int main() {
    int times;
    cin >> times;
    while (times--) {
        int ans = 9;
        cin >> S[0] >> S[1] >> S[2];
        for (int i = 0; i < (1 << 9); ++i) {
            if (doit(i)) ans = min(__builtin_popcount(i), ans);
            
        }
        cout << ans << endl;
    }
    
    

    return 0;
}
