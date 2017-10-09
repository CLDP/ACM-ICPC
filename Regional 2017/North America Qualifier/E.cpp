#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <iomanip>
using namespace std;

const int MAXN = 1010;

string P[MAXN], Q[MAXN];
double L[MAXN];
map<string, int> S;

int f[MAXN][2];
double g[MAXN][2];
bool z[MAXN][2];

vector<int> x[MAXN];

void update(int t, int &tempf, double &tempg) {
    if (f[t][0] > f[t][1]) {
        tempg = (tempg * tempf + f[t][0] * g[t][0]) / (tempf + f[t][0]);
        tempf += f[t][0];
    } else
    if (f[t][0] < f[t][1]) {
        tempg = (tempg * tempf + f[t][1] * g[t][1]) / (tempf + f[t][1]);
        tempf += f[t][1];
    } else {
        if (f[t][0] == 0) return ;
        tempg = (tempg * tempf + max(g[t][0], g[t][1]) * f[t][0]) / (tempf + f[t][0]);
        tempf += f[t][0];
    }
}

void dp(int a, int b) {
    if (z[a][b]) return ;
    z[a][b] = true;
    f[a][b] = 0;
    g[a][b] = 0;
    for (int i = 0; i < x[a].size(); ++i) {
        dp(x[a][i], 0);
        dp(x[a][i], 1);
    }

    if (b == 0) {
        for (int i = 0; i < x[a].size(); ++i) {
            update(x[a][i], f[a][b], g[a][b]);
        }
    } else {
        for (int i = 0; i < x[a].size(); ++i) {
            int t = x[a][i];
            int tempf = f[t][0] + 1;
            double tempg = (f[t][0] * g[t][0] + min(L[t], L[a])) / (f[t][0] + 1);

            for (int j = 0; j < x[a].size(); ++j) {
                if (j == i) continue;
                update(x[a][j], tempf, tempg);
            }
            if (tempf == f[a][b]) {
                g[a][b] = max(g[a][b], tempg);
            } else
            if (tempf > f[a][b]) {
                f[a][b] = tempf;
                g[a][b] = tempg;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> P[i] >> L[i] >> Q[i];
        S[P[i]] = i;
    }

    int root = -1;
    for (int i = 0; i < N; ++i) {
        if (Q[i] == "CEO") {
            root = i;
            continue;
        }
        x[S[Q[i]]].push_back(i);
    }

    dp(root, 0);
    dp(root, 1);


    if (f[root][0] == f[root][1]) {
        cout << f[root][0] << " ";
        cout << fixed << setprecision(8) << max(g[root][0], g[root][1]) << endl;
    } else
    if (f[root][0] > f[root][1]) {
        cout << f[root][0] << " ";
        cout << fixed << setprecision(8) << g[root][0] << endl;
    } else {
        cout << f[root][1] << " ";
        cout << fixed << setprecision(8) << g[root][1] << endl;
    }

    return 0;
}
