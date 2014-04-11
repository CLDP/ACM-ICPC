#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int LL[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const char TT[7] = {'w', 'X', '<', '^', '>', 'v', 'O'};

struct node {
    int x[10], y[10], dir[10];
    int z[12][12];
};

int RS[11], CS[11];
bool z[12][12];
node tempA;
vector<node> ans;


int puton(int a, int b, int dir, int t) {
    if (dir == 0) {
        for (int j = b; j < b + t; ++j) tempA.z[a][j] = 1;
        tempA.z[a][b] = 2;
        tempA.z[a][b + t - 1] = 4;
    } else {
        for (int i = a; i < a + t; ++i) tempA.z[i][b] = 1;
        tempA.z[a][b] = 3;
        tempA.z[a + t - 1][b] = 5;
    }
    return 0;
}

int dfs(int t, int a) {
    if (t == 10) {
        memset(tempA.z, 0, sizeof(tempA.z));
        for (int i = 0; i < 6; ++i) {
            puton(tempA.x[i], tempA.y[i], tempA.dir[i], LL[i]);
        }
        for (int i = 6; i < 10; ++i) tempA.z[tempA.x[i]][tempA.y[i]] = 6;
        ans.push_back(tempA);
        return 0;
    }
    if (t == 6) {
        int Sx = 0, Sy = 0;
        for (int i = 1; i <= 10; ++i) Sx += RS[i], Sy += CS[i];
        if (Sx != 4 || Sy != 4) return 0;
    }
    // Put in a row
    for (int i = 1; i <= 10; ++i) {
        if (RS[i] < a) continue;
        RS[i] -= a;
        for (int j = 1; j <= 11 - a; ++j) {
            if (t == 2 || t == 4 || t == 5 || t > 6) {
                if (make_pair(i, j) <= make_pair(tempA.x[t - 1], tempA.y[t - 1])) continue;
            }
            
            bool flag = true;
            for (int k = j; k < j + a; ++k) flag &= CS[k] > 0;
            for (int k = j - 1; k <= j + a; ++k) {
                flag &= !z[i][k] && !z[i - 1][k] && !z[i + 1][k];
            }
            if (!flag) continue;
            
            for (int k = j; k < j + a; ++k) {
                z[i][k] = true;
                --CS[k];
            }
            tempA.x[t] = i, tempA.y[t] = j, tempA.dir[t] = 0;
            if (t == 0 || t == 2 || t == 5) {
                dfs(t + 1, a - 1);
            } else {
                dfs(t + 1, a);
            }
            for (int k = j; k < j + a; ++k) {
                z[i][k] = false;
                ++CS[k];
            }
        }
        RS[i] += a;
    }
    // Put in column
    if (t >= 6) return 0;
    for (int i = 1; i <= 10; ++i) {
        if (CS[i] < a) continue;
        CS[i] -= a;
        for (int j = 1; j <= 11 - a; ++j) {
            if (t == 2 || t == 4 || t == 5 || t > 6) {
                if (make_pair(j, i) <= make_pair(tempA.x[t - 1], tempA.y[t - 1])) continue;
            }
            
            bool flag = true;
            for (int k = j; k <= j + a - 1; ++k) flag &= RS[k] > 0;
            for (int k = j - 1; k <= j + a; ++k) {
                flag &= !z[k][i] && !z[k][i - 1] && !z[k][i + 1];
            }
            if (!flag) continue;
            
            for (int k = j; k < j + a; ++k) {
                z[k][i] = true;
                --RS[k];
            }
            tempA.x[t] = j, tempA.y[t] = i, tempA.dir[t] = 1;
            if (t == 0 || t == 2 || t == 5) {
                dfs(t + 1, a - 1);
            } else {
                dfs(t + 1, a);
            }
            for (int k = j; k < j + a; ++k) {
                z[k][i] = false;
                ++RS[k];
            }
        }
        CS[i] += a;
    }
    return 0;
}



int main() {
    int N;
    cin >> N;
    for (int times = 1; times <= N; ++times) {
        for (int i = 1; i <= 10; ++i) cin >> RS[i];
        for (int i = 1; i <= 10; ++i) cin >> CS[i];
        int SS = 0;
        for (int i = 1; i <= 10; ++i) SS += RS[i] + CS[i];
        if (SS != 40) {
            cout << "Case " << times << ": 0 0" << endl;
            continue;
        }
        memset(z, 0, sizeof(z));
        ans.clear();
        dfs(0, 4);
        cout << "Case " << times << ": " << ans.size();
        if (ans.size() == 1) {
            cout << " 0" << endl;
            continue;
        }
        
        bool flag = false;
        int cnt[7], M = ans.size();
        for (int i = 1; i <= 10; ++i) 
         for (int j = 1; j <= 10; ++j) {
             if (flag) break;
             memset(cnt, 0, sizeof(cnt));
             for (int k = 0; k < M; ++k) ++cnt[ans[k].z[i][j]];
             for (int k = 0; k < 7; ++k) {
                 if (cnt[k] == 1) {
                     cout << " 1 (" << i << "," << j << ")=" << TT[k] << endl;
                     flag = true;
                     break;
                 }
             }
         }
        
        if (flag) continue;
        
        int cntt[7][7];
        for (int i = 1; i <= 10; ++i)
         for (int j = 1; j <= 10; ++j) {
             if (flag) break;
             memset(cnt, 0, sizeof(cnt));
             for (int k = 0; k < M; ++k) ++cnt[ans[k].z[i][j]];
             for (int k = 0; k < 7; ++k) {
                 if (flag) break;
                 if (cnt[k] == 0) continue;
                 for (int p = i; p <= 10; ++p) 
                  for (int q = (p == i ? j + 1 : 1); q <= 10; ++q) {
                      if (flag) break;
                      memset(cntt, 0, sizeof(cntt));
                      for (int l = 0; l < M; ++l) ++cntt[ans[l].z[i][j]][ans[l].z[p][q]];
                      for (int r = 0; r < 7; ++r) {
                          if (cntt[k][r] != 1) continue;
                          flag = true;
                          cout << " 2 (" << i << "," << j << ")=" << TT[k] 
                               <<   " (" << p << "," << q << ")=" << TT[r] << endl;
                          break;
                      }
                  }
             }
         
         }
        
        if (flag) continue;
        cout << " too ambiguous" << endl;
    }
    return 0;
}
