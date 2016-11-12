#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int A1, B1, A2, B2, A3, B3, A4, B4;
    int P = 0, Q = 0;
    cin >> A1 >> B1 >> A2 >> B2 >> A3 >> B3 >> A4 >> B4;
    for (int i = A1; i <= B1; ++i)
     for (int j = A2; j <= B2; ++j)
      for (int k = A3; k <= B3; ++k)
       for (int l = A4; l <= B4; ++l) {
           if (i + j > k + l) ++P; 
           if (i + j < k + l) ++Q;
       }
    
    if (P > Q) cout << "Gunnar" << endl;
    if (P < Q) cout << "Emma" << endl;
    if (P == Q) cout << "Tie" << endl;

    return 0;
}
