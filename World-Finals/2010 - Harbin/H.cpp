#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3010;
const double PI = acos(-1.0);

int N, M;
int X[MAXN], Y[MAXN], H[MAXN], Level[MAXN];
bool z[MAXN];
map<pair<int, int>, bool> EdgeSet;
vector<int> Height;
vector<pair<double, int> > E[MAXN];

int Union_H[MAXN], f[MAXN], Union_num;
int Union_E[MAXN][MAXN];
bool Union_NearSea[MAXN];


int AddEdge(int a, int b) {
    EdgeSet[make_pair(a, b)] = true;
    double deg = atan2((double)(Y[b] - Y[a]), (double)(X[b] - X[a]));
    E[a].push_back(make_pair(deg, b));
    return 0;
}

int FloodFill(int a, int p) {
    if (z[a]) return 0;
    z[a] = true;
    f[a] = p;
    for (int i = 0; i < E[a].size(); ++i)
     if (H[E[a][i].second] == H[a]) FloodFill(E[a][i].second, p);
    return 0;
}

int Init() {
    Height.clear();
    map<string, int> C;
    for (int i = 1; i <= N; ++i) {
        string S;
        cin >> S >> X[i] >> Y[i] >> H[i];
        Height.push_back(H[i]);
        C[S] = i;
        E[i].clear();
    }
    sort(Height.begin(), Height.end());
    Height.erase(unique(Height.begin(), Height.end()), Height.end());
    EdgeSet.clear();
    for (int i = 1; i <= M; ++i) {
        string u, v;
        cin >> u >> v;
        AddEdge(C[u], C[v]);
        AddEdge(C[v], C[u]);
    }
    vector<bool> NearSea(N + 1, false);
    for(int i = 1; i <= N; ++i) {
        sort(E[i].begin(), E[i].end());
        int ES = E[i].size();
        for (int a = 0; a + 1 < ES; ++a)
         if ((E[i][a + 1].first - E[i][a].first) >= PI) NearSea[i] = true;
        if (E[i][0].first + 2 * PI - E[i][ES - 1].first >= PI) NearSea[i] = true;
        for (int a = 0; a < ES; ++a) {
            int b = (a + 1) % ES;
            if (EdgeSet.find(make_pair(E[i][a].second, E[i][b].second)) == EdgeSet.end()) NearSea[i] = true;
        }
    }
    
    Union_num = 0;
    memset(z, 0, sizeof(z));
    for (int i = 1; i <= N; ++i)
     if (!z[i]) FloodFill(i, ++Union_num);
     
    for (int i = 1; i <= Union_num; ++i) Union_NearSea[i] = false;
    for (int i = 1; i <= Union_num; ++i) Union_E[i][0] = 0;
    for (int i = 1; i <= N; ++i) Union_H[f[i]] = H[i];
    for (int i = 1; i <= N; ++i) {
        if (NearSea[i]) Union_NearSea[f[i]] = true;
        for (int j = 0; j < E[i].size(); ++j)
         if (f[i] != f[E[i][j].second])
          Union_E[f[i]][++Union_E[f[i]][0]] = f[E[i][j].second];
    }
    return 0;
}

int Dfs(int a, int hi) {
    if (z[a]) return 0;
    z[a] = true;
    for (int i = 1; i <= Union_E[a][0]; ++i) {
        if (Union_H[Union_E[a][i]] >= hi) continue;
        if (z[Union_E[a][i]]) {
            swap(Union_E[a][i], Union_E[a][Union_E[a][0]]);
            --Union_E[a][0];
            --i;
        } else {
            Dfs(Union_E[a][i], hi);
        }
    }
    return 0;
}

int Solve() {
    vector<int> Union_Level(Union_num + 1, 0);
    for (int i = 0; i < Height.size(); ++i) {
        memset(z, 0, sizeof(z));
        for (int j = 1; j <= Union_num; ++j)
         if (Union_NearSea[j] && Union_H[j] < Height[i]) {
             Dfs(j, Height[i]);
         }
        for (int j = 1; j <= Union_num; ++j)
         if (!z[j]) Union_Level[j] = Height[i];
    }
    for (int i = 1; i <= N; ++i) Level[i] = Union_Level[f[i]];
    return 0;
}

int FindLake(int a) {
    if (z[a]) return 0;
    z[a] = true;
    for (int i = 0; i < E[a].size(); ++i)
     if (H[E[a][i].second] < Level[E[a][i].second] && Level[a] == Level[E[a][i].second]) {
         FindLake(E[a][i].second);
     }
    return 0;
}

int Output(int &times) {
    vector<int> Lake;
    memset(z, 0, sizeof(z));
    for (int i = 1; i <= N; ++i)
     if (!z[i] && H[i] < Level[i]) {
         Lake.push_back(Level[i]);
         FindLake(i);
     }
    
    cout << "Case " << ++times << ":" << endl;
    if (Lake.empty()) {
        cout << "  0" << endl;
    } else {
        sort(Lake.begin(), Lake.end());
        for (int i = 0; i < Lake.size(); ++i) cout << "  " << Lake[i] << endl;
    }
    return 0;
}

int main() {
    int times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        Init();
        Solve();
        Output(times);
    }
    return 0;
}
