#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;

string x[4];
bool z[4][4];
bool len[10];
int maxL = 0;
map<string, int> word;

int dfs(int a, int b, string temp) {
    if (len[temp.size()]) {
        if (word.find(temp) != word.end()) word[temp] = 1;
    }
    if (temp.size() == maxL) return 0;
    
    if (a > 0) {
        if (b > 0 && !z[a-1][b-1]) {
            z[a-1][b-1] = true;
            dfs(a-1, b-1, temp + x[a-1][b-1]);
            z[a-1][b-1] = false;
        }
        if (b < 3 && !z[a-1][b+1]) {
            z[a-1][b+1] = true;
            dfs(a-1, b+1, temp + x[a-1][b+1]);
            z[a-1][b+1] = false;
        }
        if (!z[a-1][b]) {
            z[a-1][b] = true;
            dfs(a-1, b, temp + x[a-1][b]);
            z[a-1][b] = false;
        }
    }
    if (a < 3) {
        if (b > 0 && !z[a+1][b-1]) {
            z[a+1][b-1] = true;
            dfs(a+1, b-1, temp + x[a+1][b-1]);
            z[a+1][b-1] = false;
        }
        if (b < 3 && !z[a+1][b+1]) {
            z[a+1][b+1] = true;
            dfs(a+1, b+1, temp + x[a+1][b+1]);
            z[a+1][b+1] = false;
        }
        if (!z[a+1][b]) {
            z[a+1][b] = true;
            dfs(a+1, b, temp + x[a+1][b]);
            z[a+1][b] = false;
        }
    }
    if (b > 0 && !z[a][b-1]) {
        z[a][b-1] = true;
        dfs(a, b-1, temp + x[a][b-1]);
        z[a][b-1] = false;
    }
    if (b < 3 && !z[a][b+1]) {
        z[a][b+1] = true;
        dfs(a, b+1, temp + x[a][b+1]);
        z[a][b+1] = false;
    }
    
    return 0;
}


int main() {
    int n, m;
    cin >> n;
    string p;
    for (int i = 0; i < n; ++i) {
        cin >> p;
        word[p] = 0;
        len[p.size()] = true;
        if (p.size() > maxL) maxL = p.size();
    }
    
    cin >> m;
    while (m > 0) {
        --m;
        for (int i = 0; i < 4; ++i) cin >> x[i];
        for (int i = 0; i < 4; ++i) 
         for (int j = 0; j < 4; ++j) {
             z[i][j] = true;
             string temp = "";
             temp = temp + x[i][j];
             dfs(i, j, temp);
             z[i][j] = false;
         }
        
        map<string, int>::iterator iter = word.begin();
        
        int ans = 0, ansL = 0, ansN = 0;
        string ansP;
        while (iter != word.end()) {
            if ((iter->first).size() < 3 && iter->second == 1) {
                ansN += 1;
            } else
            if ((iter->first).size() == 3 && iter->second == 1) {
                ans += 1;
                ansN += 1;
            } else
            if ((iter->first).size() == 4 && iter->second == 1) {
                ans += 1;
                ansN += 1;
            } else
            if ((iter->first).size() == 5 && iter->second == 1) {
                ans += 2;
                ansN += 1;
            } else
            if ((iter->first).size() == 6 && iter->second == 1) {
                ans += 3;
                ansN += 1;
            } else
            if ((iter->first).size() == 7 && iter->second == 1) {
                ans += 5;
                ansN += 1;
            } else
            if ((iter->first).size() == 8 && iter->second == 1) {
                ans += 11;
                ansN += 1;
            }
            if ((iter->first).size() > ansL && iter->second == 1) {
                ansP = iter->first;
                ansL = (iter->first).size();
            }
            iter->second = 0;
            ++iter;
        }
        cout << ans << " " << ansP << " " << ansN << endl;
    }
    
    return 0;
}
