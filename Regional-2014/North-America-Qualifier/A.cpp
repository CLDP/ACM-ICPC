#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string x[10];

int A[100], B[100], C[100], D[100];

int main() {
    for (int i = 0; i < 8; ++i) cin >> x[i];
    
    int N = 0;
    for (int i = 0; i < 8; ++i)
     for (int j = 0; j < 8; ++j) 
      if (x[i][j] == '*') {
          ++N;
          ++A[i + j];
          ++B[10 + i - j];
          ++C[i];
          ++D[j];
      }
     
     for (int i = 0; i < 100; ++i) 
      if (A[i] > 1 || B[i] > 1 || C[i] > 1 || D[i] > 1) N = 100;
     
     if (N == 8) cout << "valid" << endl; else cout << "invalid" << endl;
    
    

    return 0;
}
