#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string s[20];
long long x[20][20];

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        map<string, int> C;
        for (int i = 0; i < N; ++i) {
            cin >> s[i];
            C[s[i]] = i;
        }
        string s1, s2, equ;
        int M;
        memset(x, 0, sizeof(x));
        for (int i = 0; i < N - 1; ++i) {
            cin >> s1 >> equ >> M >> s2;
            x[C[s1]][C[s2]] = M;
        }
        
        int T = 0;
        for (int i = 0; i < N; ++i) {
            double D[20];
            memset(D, 0, sizeof(D));
            D[i] = 1;
            for (int times = 0; times < N; ++times)
             for (int j = 0; j < N; ++j)
              for (int k = 0; k < N; ++k)
               if (x[j][k]) {
                   if (D[k] < 1e-10 && D[j] > 0) D[k] = D[j] * x[j][k];
                   if (D[j] < 1e-10 && D[k] > 0) D[j] = D[k] / x[j][k];
               }
             bool flag = true;
             for (int j = 0; j < N; ++j) flag &= (D[j] >= 1);
             if (flag) {
                 T = i;
                 break;
             }
        }
        long long D[20];
        memset(D, 0, sizeof(D));
        D[T] = 1;
        for (int times = 0; times < N; ++times)
         for (int j = 0; j < N; ++j)
          for (int k = 0; k < N; ++k)
           if (x[j][k]) {
               if (D[k] == 0 && D[j] > 0) D[k] = D[j] * x[j][k];
               if (D[j] == 0 && D[k] > 0) D[j] = D[k] / x[j][k];
           }
            
        vector<pair<long long, int> > X;
        for (int i = 0; i < N; ++i) X.push_back(make_pair(D[i], i));
        sort(X.begin(), X.end());
        cout << X[0].first << s[X[0].second];
        for (int i = 1; i < N; ++i)
            cout << " = " << X[i].first << s[X[i].second];
        
        cout << endl;
    }
    
    return 0;
}
