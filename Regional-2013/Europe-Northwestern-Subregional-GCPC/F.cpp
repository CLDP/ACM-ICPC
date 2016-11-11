#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;

int ans;
string p[5];

int dfs(int temp) {
    if (temp > ans) ans = temp;
    for (int i = 0; i < 5; ++i)
     for (int j = 0; j < 9; ++j) 
      if (p[i][j] == 'o') {
          if (i > 1 && p[i-1][j] == 'o' && p[i-2][j] == '.') {
              p[i][j] = '.';
              p[i-1][j] = '.';
              p[i-2][j] = 'o';
              dfs(temp + 1);
              p[i][j] = 'o';
              p[i-1][j] = 'o';
              p[i-2][j] = '.';
          }
          if (j > 1 && p[i][j-1] == 'o' && p[i][j-2] == '.') {
              p[i][j] = '.';
              p[i][j-1] = '.';
              p[i][j-2] = 'o';
              dfs(temp + 1);
              p[i][j] = 'o';
              p[i][j-1] = 'o';
              p[i][j-2] = '.';
          }
          if (j < 7 && p[i][j+1] == 'o' && p[i][j+2] == '.') {
              p[i][j] = '.';
              p[i][j+1] = '.';
              p[i][j+2] = 'o';
              dfs(temp + 1);
              p[i][j] = 'o';
              p[i][j+1] = 'o';
              p[i][j+2] = '.';
          }
          if (i < 3 && p[i+1][j] == 'o' && p[i+2][j] == '.') {
              p[i][j] = '.';
              p[i+1][j] = '.';
              p[i+2][j] = 'o';
              dfs(temp + 1);
              p[i][j] = 'o';
              p[i+1][j] = 'o';
              p[i+2][j] = '.';
          }
      }
      
    return 0;
}


int main() {
    int n;
    cin >> n;
    while (n--) {
        for (int i = 0; i < 5; ++i) cin >> p[i];
        int total = 0;
        for (int i = 0; i < 5; ++i)
         for (int j = 0; j < 9; ++j)
          if (p[i][j] == 'o') total += 1;
        ans = 0;
        dfs(0);
        cout << total - ans << " " << ans << endl;
    }
    
    return 0;
}
