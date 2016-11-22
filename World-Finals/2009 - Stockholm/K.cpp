#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

vector<pair<string, string> > w[22];
vector<int> C[22];
long long f[210][210];

int main() {
    int times = 0;
    string s1, s2;
    while (cin >> s1) {
        if (s1 == ".") break;
        int M;
        cin >> s2 >> M;
        
        string ts1, ts2;
        int l = s1.length();
        for (int i = 1; i <= s1.length(); ++i) {
            w[i].clear();
            C[i].clear();
            w[i].push_back(make_pair(s1[s1.length() - i] + ts1, ts1));
            w[i].push_back(make_pair(s2[s2.length() - i] + ts2, ts2));
            ts1 = s1[s1.length() - i] + ts1;
            ts2 = s2[s2.length() - i] + ts2;
        }
        
        for (int i = 0; i < M; ++i) {
            cin >> s1 >> s2;
            string ts1, ts2;
            for (int j = 1; j <= s1.length(); ++j) {
                w[j].push_back(make_pair(s1[s1.length() - j] + ts1, ts1));
                w[j].push_back(make_pair(s2[s2.length() - j] + ts2, ts2));
                ts1 = s1[s1.length() - j] + ts1;
                ts2 = s2[s2.length() - j] + ts2;
            }
            C[s1.length()].push_back(w[s1.length()].size() - 2);
        }
        
        map<pair<string, string>, long long> pre;
        for (int i = 1; i <= l; ++i) {
            for (int j = 0; j < w[i].size(); ++j)
             for (int k = 0; k < w[i].size(); ++k) f[j][k] = -1;

            for (int j = 0; j < C[i].size(); ++j) f[C[i][j]][C[i][j] + 1] = 1;
            for (int j = 0; j < w[i].size(); ++j)
             for (int k = 0; k < w[i].size(); ++k) {
                 if (w[i][j] == w[i][k])
                     f[j][k] = 0;
                 else 
                 if (i > 1 && w[i][j].first[0] == w[i][k].first[0]
                  && pre.find(make_pair(w[i][j].second, w[i][k].second)) != pre.end()
                  && ((pre[make_pair(w[i][j].second, w[i][k].second)] < f[j][k]) || (f[j][k] == -1)))
                     f[j][k] = pre[make_pair(w[i][j].second, w[i][k].second)];
             }
            
            for (int k = 0; k < w[i].size(); ++k)
             for (int a = 0; a < w[i].size(); ++a)
              for (int b = 0; b < w[i].size(); ++b)
               if ((f[a][k] != -1) && (f[k][b] != -1) && ((f[a][b] == -1) || (f[a][b] > f[a][k] + f[k][b])))
                f[a][b] = f[a][k] + f[k][b];
                
            pre.clear();
            for (int j = 0; j < w[i].size(); ++j)
             for (int k = 0; k < w[i].size(); ++k)
              if (f[j][k] > -1) {
                  if (pre.find(make_pair(w[i][j].first, w[i][k].first)) == pre.end())
                      pre[make_pair(w[i][j].first, w[i][k].first)] = f[j][k];
                  else 
                  if (pre[make_pair(w[i][j].first, w[i][k].first)] > f[j][k])
                      pre[make_pair(w[i][j].first, w[i][k].first)] = f[j][k];
              }
        }
        
        if (f[0][1] > -1)
            cout << "Case " << ++times << ": " << f[0][1] << endl;
        else
            cout << "Case " << ++times << ": No solution" << endl;
    }
    
    return 0;
}
