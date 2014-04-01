#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;


int x[110][110], y[110][110], z[110][110];

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) cin >> x[i][j];
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) cin >> y[i][j];
        
        int ans = 0;
        for (int k = 0; k < 4; ++k) {
            int temp = 0;
            for (int i = 0; i < N; ++i)
             for (int j = 0; j < N; ++j) temp += x[i][j] == y[i][j];
            if (temp > ans) ans = temp;
            for (int i = 0; i < N; ++i)
             for (int j = 0; j < N; ++j) z[j][N - 1 - i] = x[i][j];
            for (int i = 0; i < N; ++i)
             for (int j = 0; j < N; ++j) x[i][j] = z[i][j];
        }
        cout << ans << endl;
    }
    return 0;
}
