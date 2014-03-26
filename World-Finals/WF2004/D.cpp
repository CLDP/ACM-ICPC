#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

bool z[42];
int PS[26], TS[26];
vector<int> PP[42][42];


int main() {
    for (int l = 1; l <= 40; ++l) {
        for (int j = 0; j <= 40; ++j) {
            queue<int> QE;
            for (int i = 0; i < l; ++i) QE.push(i);
            PP[l][j].clear();
            for (int i = 0; i < l; ++i) {
                PP[l][j].push_back(QE.front());
                QE.pop();
                
                if (i == l - 1) break;
                for (int fly = 0; fly < j; ++fly) {
                    QE.push(QE.front());
                    QE.pop();
                }
            }
        }
    }
    
    int times = 0;
    string P, Q;
    while (cin >> P) {
        if (P == "X") break;
        int ans = 0;
        int m = P.size();
        memset(PS, 0, sizeof(PS));
        for (int i = 0; i < m; ++i) ++PS[P[i] - 'A'];
        string Q;
        for (int l = m / 2; l > 0 && ans == 0; --l) {
             for (int s = 0; s < m; ++s)
              for (int i = 0; i < m - 1; ++i) {
                  if (ans > 1) break;
                  
                  memset(z, 0, sizeof(z));
                  string T;
                  for (int k = 0; k < l; ++k) {
                      T = T + P[(PP[m][i][k] + s) % m];
                      z[(PP[m][i][k] + s) % m] = true;
                  }
                  if (T == Q) continue;
                  
                  // Special check
                  memset(TS, 0, sizeof(TS));
                  for (int j = 0; j < l; ++j) ++TS[T[j] - 'A'];
                  bool flag = true;
                  for (int j = 0; j < 26; ++j) 
                   if (TS[j] + TS[j] > PS[j]) {
                       flag = false;
                       break;
                   }
                  if (!flag) continue;
                  
                  for (int t = 0; t < m; ++t) {
                      if (z[t]) continue;
                      
                      vector<int> CQ;
                      for (int j = t; j < m; ++j)
                       if (!z[j]) CQ.push_back(j);
                      for (int j = 0; j < t; ++j)
                       if (!z[j]) CQ.push_back(j);
                      
                      bool flag = false;
                      for (int j = i + 1; j < m; ++j) {
                          flag = true;
                          for (int k = 0; k < l; ++k) {
                              if (T[k] != P[CQ[PP[m - l][j][k]]]) {
                                  flag = false;
                                  break;
                              }
                          }
                          if (flag && Q != T) ++ans, Q = T;
                          if (flag) break;
                      }
                      if (flag) break;
                  }
              }
        }
        cout << "Code " << ++times << ": ";
        if (ans > 1) 
            cout << "Codeword not unique" << endl; 
        else 
            cout << Q << endl;
    }

    return 0;
}
