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

int x[110], y[110];
int z[110][110];

int main() {
    int times;
    cin >> times;
    while (times--) {
        int N;
        cin >> N;
        vector<pair<int, int> > X, Y;
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
            X.push_back(make_pair(x[i], i));
        }
        for (int i = 0; i < N; ++i) {
            cin >> y[i];
            Y.push_back(make_pair(y[i], i));
        }
        sort(X.begin(), X.end());
        sort(Y.begin(), Y.end());
        int a = 0, b = 0, ans1 = 0, ans2 = 0;
        memset(z, -1, sizeof(z));
        while (a < N || b < N) {
            int T = min(X[a].first, Y[b].first);
            int T1 = 0, T2 = 0;
            while (a < N && X[a].first == T) {
                for (int i = 0; i < N; ++i) 
                 if (z[X[a].second][i] == -1) z[X[a].second][i] = T;
                ++T1;
                ++a;
            }
            while (b < N && Y[b].first == T) {
                for (int i = 0; i < N; ++i) 
                 if (z[i][Y[b].second] == -1) z[i][Y[b].second] = T;
                ++T2;
                ++b;
            }
            ans1 += max(T1, T2) * T;
        }
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) ans2 += z[i][j];
        
        cout << "Minimalni budova obsahuje " << ans1 << " kostek, maximalni " << ans2 << " kostek." << endl;
    }
    return 0;
}
