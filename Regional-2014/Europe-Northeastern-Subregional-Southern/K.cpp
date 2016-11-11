#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[2010][2010];


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= N; ++j) scanf("%d", &x[i][j]);
        
        set<int> S;
        S.insert(1);
        S.insert(x[1][2]);
        cout << "1 " << x[1][2] << endl;
        for (int i = 3; i <= N; ++i) {
            int A = x[1][i];
            for (int j = 1; j <= N; ++j) {
                if (S.find(x[A][j]) != S.end()) {
                    cout << x[A][j] << " " << A << endl;
                    S.insert(A);
                    break;
                }
            }
        }
        
        cout << endl;
    }
    return 0;
}
