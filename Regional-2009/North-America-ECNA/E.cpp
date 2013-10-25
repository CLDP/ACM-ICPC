#include <iostream>
using namespace std;

const int MAXN = 101;

int n, m;
int x[MAXN][MAXN], y[MAXN][MAXN];

int dfs(int a, int b, int h) {
    if ((x[a][b] > 0 && x[a][b] <= h) || (x[a][b] < 0 && x[a][b] != -h)) 
        x[a][b] = -h;
    else
        return 0;
        
    if (a > 0) dfs(a-1, b, h);
    if (a < n - 1) dfs(a+1, b, h);
    if (b > 0) dfs(a, b-1, h);
    if (b < m - 1) dfs(a, b+1, h);
    return 0;
}

int dfsY(int a, int b) {
    y[a][b] = 0;
    if (a > 0 && y[a-1][b] > 0) dfsY(a-1, b);
    if (a < n-1 && y[a+1][b] > 0) dfsY(a+1, b);
    if (b > 0 && y[a][b-1] > 0) dfsY(a, b-1);
    if (b < m-1 && y[a][b+1] > 0) dfsY(a, b+1);
    return 0;
}

bool check() {
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) y[i][j] = x[i][j];
    
    bool ans = false;
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) 
      if (y[i][j] > 0) {
          if (ans) return true;
          ans = true;
          dfsY(i, j);
      }
    
    return false;   
}

int main() {
    int times = 0;
    while (cin >> n >> m) {
        ++times;
        if (n == 0) break;
        int height = 0;
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < m; ++j) {
             cin >> x[i][j];
             if (x[i][j] > height) height = x[i][j];
         }
        
        bool flag = false;
        for (int h = 1; h <= height; ++h) {
            for (int i = 0; i < n; ++i) {
                if (x[i][0] != -h) dfs(i, 0, h);
                if (x[i][m-1] != -h) dfs(i, m-1, h);
            }
            for (int j = 0; j < m; ++j) {
                if (x[0][j] != -h) dfs(0, j, h);
                if (x[n-1][j] != -h) dfs(n-1, j, h);
            }
            
            if (check()) {
                flag = true;
                cout << "Case " << times << ": Island splits when ocean rises " << h << " feet." << endl;
                break;
            }
        }
        
        if (!flag) {
            cout << "Case " << times << ": Island never splits." << endl;
        }
    }
    
    return 0;
}
