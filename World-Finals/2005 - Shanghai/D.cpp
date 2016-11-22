#include <vector>
#include <iostream>
using namespace std;

int x[52], z[11];
int s[11][52];
int ansT;
vector<pair<int, int> > ans;


int dfs(int T, int x[], int diff) {
    if (T == 0) {
        if (diff > 0) return 0;
        
        int num = 0;
        for (int i = 1; i <= 10; ++i)
         if (z[i] != -1) ++num;
        if (num < ansT) {
            ansT = num;
            ans.clear();
            for (int j = 1; j <= 10; ++j) {
                if (z[j] == -1) continue;
                ans.push_back(make_pair(j, z[j]));
            }
        } else 
        if (num == ansT) {
            vector<pair<int, int> > temp;
            for (int j = 1; j <= 10; ++j) {
                if (z[j] == -1) continue;
                temp.push_back(make_pair(j, z[j]));
            }
            for (int i = 0; i < num; ++i) {
                if (temp[i].second < ans[i].second) {
                    ans = temp;
                    return 0;
                }
            }
        }
        return 0;
    }
    
    int y[52];
    z[T] = -1;
    for (int k = 0; k < 26; ++k) {
        y[k] = x[k * 2 + 1];
        y[k + 26] = x[k * 2];
    }
    
    diff = 0;
    for (int i = 0; i < 52; ++i) diff += (y[i] != s[T - 1][i]);
    if (diff <= 2 * (T - 1)) dfs(T - 1, y, diff);
    
    for (int i = 0; i < 51; ++i) {
        diff -= (y[s[1][i]] != s[T - 1][s[1][i]]) + (y[s[1][i + 1]] != s[T - 1][s[1][i + 1]]);
        swap(y[s[1][i]], y[s[1][i + 1]]);
        diff += (y[s[1][i]] != s[T - 1][s[1][i]]) + (y[s[1][i + 1]] != s[T - 1][s[1][i + 1]]);
        z[T] = i;
        if (diff <= 2 * (T - 1)) dfs(T - 1, y, diff);
        diff -= (y[s[1][i]] != s[T - 1][s[1][i]]) + (y[s[1][i + 1]] != s[T - 1][s[1][i + 1]]);
        swap(y[s[1][i]], y[s[1][i + 1]]);
        diff += (y[s[1][i]] != s[T - 1][s[1][i]]) + (y[s[1][i + 1]] != s[T - 1][s[1][i + 1]]);
    }
    
    return 0;
}


int main() {
    for (int i = 0; i < 52; ++i) s[0][i] = i;
    for (int i = 1; i <= 10; ++i) {
        for (int j = 0; j < 52; j += 2) s[i][j] = s[i - 1][26 + j / 2];
        for (int j = 1; j < 52; j += 2) s[i][j] = s[i - 1][j / 2];
    }
    
    int times;
    cin >> times;
    for (int tt = 1; tt <= times; ++tt) {
        for (int i = 0; i < 52; ++i) cin >> x[i];
        int T = 0, diff;
        for (int i = 0; i < 11; ++i) {
            diff = 0;
            for (int j = 0; j < 52; ++j) diff += (x[j] != s[i][j]);
            if (diff < 26) {
                T = i;
                break;
            }
        }
        
        ansT = 11;
        ans.clear();
        for (int i = 0; i <= 10; ++i) z[i] = -1;
        dfs(T, x, diff);
        
        cout << "Case " << tt << endl;
        cout << "Number of shuffles = " << T << endl;
        if (ans.size() == 0) {
            cout << "No error in any shuffle" << endl;
        } else {
            for (int i = 0; i < ansT; ++i)
                cout << "Error in shuffle " << ans[i].first << " at location " << ans[i].second << endl;
        }
        cout << endl;
    }
    return 0;
}
