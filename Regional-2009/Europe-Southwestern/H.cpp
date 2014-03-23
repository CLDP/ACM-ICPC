#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 8210;


int getA(int N, vector<int> &x, vector<int> &y, string &A, string &B) {
    A = B = "";
    map<int, int> C;
    map<int, int> D;
    for (int i = 0; i < (1 << N); ++i) C[y[i]] = i, D[x[i]] = i;
    
    for (int i = 0; i < (1 << (N - 1)); ++i) {
        A = A + "0";
        B = B + "0";
    }
    
    vector<bool> z((1 << N), false);
    for (int i = 0; i < (1 << N); i += 2) {
        if (z[i]) continue;
        bool flag = false;
        int j = i;
        while (!z[j / 2 * 2]) {
            if (j & 1) --j; else ++j;
            if (flag) A[j / 2] = '1';
            z[j / 2 * 2] = true;
            int c = C[x[j]];
            bool first = (j % 2 == 0 && !flag) || (j % 2 == 1 && flag);
            
            if (first != (c % 2 == 0)) B[c / 2] = '1';
            if (c & 1) --c; else ++c;
            j = D[y[c]];
            first = (c % 2 == 0 && B[c / 2] == '0') || (c % 2 == 1 && B[c / 2] == '1');
            flag = (first != (j % 2 == 0));
        }
    }
    return 0;
}

int deal(int N, vector<int> &x, vector<int> &y, vector<string> &P) {
    if (N == 1) {
        if (x[0] == y[0]) {
            P[0] = "0"; 
        } else {
            P[0] = "1";
        }
        
        return 0;
    }
    
    string A, B;
    getA(N, x, y, A, B);
    P[0] = A;
    P[2 * N - 2] = B;
    
    vector<int> xx, yy;
    for (int i = 0; i < (1 << (N - 1)); ++i) {
        if (A[i] == '0') {
            xx.push_back(x[i * 2]);
        } else {
            xx.push_back(x[i * 2 + 1]);
        }
        if (B[i] == '0') {
            yy.push_back(y[i * 2]);
        } else {
            yy.push_back(y[i * 2 + 1]);
        }
    }
    vector<string> PP(2 * (N - 1) - 1);
    deal(N - 1, xx, yy, PP);
    
    for (int i = 1; i < 2 * N - 2; ++i) P[i] = PP[i - 1];
    
    xx.clear();
    yy.clear();
    
    for (int i = 0; i < (1 << (N - 1)); ++i) {
        if (A[i] == '1') {
            xx.push_back(x[i * 2]);
        } else {
            xx.push_back(x[i * 2 + 1]);
        }
        if (B[i] == '1') {
            yy.push_back(y[i * 2]);
        } else {
            yy.push_back(y[i * 2 + 1]);
        }
    }
    
    PP = vector<string>(2 * (N - 1) - 1);
    
    deal(N - 1, xx, yy, PP);
    for (int i = 1; i < 2 * N - 2; ++i) P[i] = P[i] + PP[i - 1];
    
    return 0;
}


int main() {
    int N;
    bool first = true;
    while (cin >> N) {
        if (N == 0) break;
        if (!first) cout << endl;
        first = false;
        
        vector<int> x((1 << N), 0), y((1 << N), 0);
        for (int i = 0; i < (1 << N); ++i) {
            x[i] = i;
            cin >> y[i];
        }
        
        vector<string> P(2 * N - 1);
        deal(N, x, y, P);
        
        for (int i = 0; i < 2 * N - 1; ++i) cout << P[i] << endl;
    }
    
    return 0;
}
