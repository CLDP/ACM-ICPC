#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 100000;
const int INF = 1000000000;

struct node {
    int m, s, n, t;
    bool operator < (node const & B) {
        if (m + n != B.m + B.n) return m + n < B.m + B.n;
        if (B.s != s) return s < B.s;
        if (B.m != m) {
            if (m < B.m && t < s) return true;
            if (B.m < m && B.t > s) return true;
            return false;
        }
        return t < B.t;
    }
};


int x[10][MAXN], y[10], xs[10];

bool equal(const node &A, const int &B) {
    if (A.n + A.m >= 6) return false;
    int temp = 0;
    for (int i = 0; i < A.m; ++i) temp = temp * 10 + A.s;
    for (int i = 0; i < A.n; ++i) temp = temp * 10 + A.t;
    return temp == B;
}


int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        memset(x, 0, sizeof(x));
        for (int i = 1; i < 10; ++i) {
            int temp = 0, j = 0;
            while (x[i][temp] == 0) {
                x[i][temp] = j++;
                temp = (temp * 10 + i) % N;
            }
            y[i] = j - x[i][temp];
            xs[i] = x[i][temp];
        }
        
        node ans;
        ans.m = INF;
        ans.s = 9;
        for (int i = 1; i < 10; ++i) 
         for (int j = 1; j <= i; ++j) 
          for (int k = 0; k < N; ++k) {
              if (x[i][k] == 0 || x[j][k] == 0) continue;
              int R = x[i][k], L = x[j][k];
              if (R <= L && R < xs[i]) continue;
              while (R <= L) R += y[i];
              if (L >= xs[j]) {
                  while (L + y[j] < R) L += y[j];
              }
              node temp;
              temp.m = R - L;
              temp.s = i;
              temp.n = L;
              temp.t = i - j;
              if (equal(temp, N)) {
                  if (L - y[j] >= xs[j]) {
                      temp.m += y[j];
                      temp.n -= y[j];
                  } else {
                      if (R < xs[i]) continue;
                      R += y[i];
                      if (L >= xs[j]) {
                          while (L + y[j] < R) L += y[j];
                      }
                      temp.m = R - L;
                      temp.n = L;
                  }
              }
              if (temp < ans) ans = temp;
          }
            
        for (int i = 1; i < 10; ++i) 
         for (int j = 1; i + j < 10; ++j) 
          for (int k = 0; k < N; ++k) {
              if (x[i][k] == 0 || x[j][(N - k) % N] == 0) continue;
              int R = x[i][k], L = x[j][(N - k) % N];
              if (R <= L && R < xs[i]) continue;
              
              while (R <= L) R += y[i];
              node temp;
              temp.m = R - L;
              temp.s = i;
              temp.n = L;
              temp.t = i + j;
              if (equal(temp, N)) {
                  if (L >= xs[j] && L + y[j] < R) {
                      temp.m -= y[j];
                      temp.n += y[j];
                  } else {
                      if (R < xs[i]) continue;
                      R += y[i];
                      temp.m = R - L;
                      temp.n = L;
                  }
              }
              if (temp < ans) ans = temp;
          }
        cout << N << ": " << ans.m << " " << ans.s << " " << ans.n << " " << ans.t << endl;
    }
    return 0;
}
