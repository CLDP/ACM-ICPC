#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;


string P[20], Q[20];

int trans(int N) {
    char R[20][20];
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < N; ++j) R[j][N - 1 - i] = P[i][j];
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < N; ++j) P[i][j] = R[i][j];
    return 0;
}


int main() {
    int N, M = 0;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
        if (P[i].size() != N) {
            cout << "invalid grille" << endl;
            return 0;
        }
        for (int j = 0; j < N; ++j) M += P[i][j] == '.';
        Q[i] = string(N, '.');
    }
    if (M * 4 != N * N) {
        cout << "invalid grille" << endl;
        return 0;
    }
    string R;
    cin >> R;
    int k = 0;
    for (int t = 0; t < 4; ++t) {
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) 
          if (P[i][j] == '.') Q[i][j] = R[k++];

        trans(N);
    } 

    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < N; ++j) {
          if (Q[i][j] == '.') {
              cout << "invalid grille" << endl;
              return 0;
          }
     }

    for (int i = 0; i < N; ++i) cout << Q[i];
    cout << endl;

    return 0;
}
