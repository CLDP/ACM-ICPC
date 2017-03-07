#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

const double EPS = 1e-14;
const int MAXN = 10010;
const int MAXM = 21;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int N, M;
double PR[4];
string X[MAXN];
int Y[MAXN][MAXM];
map<int, double> x[MAXN * MAXM];
vector<int> y[MAXN * MAXM];
double ans[MAXN * MAXM];

int dcmp(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

bool inside(int a, int b) {
    return 0 <= a && a < N && 0 <= b && b < M;
}

void bfs(int &MM, double &base) {
    queue<pair<int, int> > Q;
    for (int i = 0; i < M; ++i) {
        if (X[0][i] == '.') {
            base += 1;
            Q.push(make_pair(0, i));
            Y[0][i] = ++MM;
        }
    }
    while (!Q.empty()) {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        for (int k = 0; k < 4; ++k) {
            int a = i + MX[k], b = j + MY[k];
            if (inside(a, b) && X[a][b] != 'X' && Y[a][b] == 0) {
                Y[a][b] = ++MM;
                if (X[a][b] == '.') Q.push(make_pair(a, b));
            }
        }
    }

    MM = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (Y[i][j] > 0) Y[i][j] = ++MM;
        }
    }
    base = 1 / base;
}

void add(int a, int b, double c) {
    x[a][b] = c;
    y[b].push_back(a);
}

double find(int a, int b, int i, int j) {
    double S = 0, E = 0;
    for (int k = 0; k < 4; ++k) {
        int c = a + MX[k], d = b + MY[k];
        if (inside(c, d) && X[c][d] != 'X') S += PR[k];
        if (c == i && d == j) E = PR[k];
    }
    return E / S;
}

void gauss(int N) {
    for (int i = 1; i <= N; ++i) {
        int j = i;
        for (int j = 0; j < y[i].size(); ++j) {
            if (y[i][j] <= i) continue;
            int a = y[i][j];
            if (dcmp(x[a][i]) == 0) continue;
            double temp = x[a][i] / x[i][i];
            for (auto it = x[i].begin(); it != x[i].end(); ++it) {
                if (x[a].find(it->first) == x[a].end()) {
                    y[it->first].push_back(a);
                    x[a][it->first] = 0;
                }
                x[a][it->first] -= temp * it->second;
                if (dcmp(x[a][it->first]) == 0) x[a].erase(it->first);
            }
        }
    }
    
    for (int i = N; i >= 1; --i) {
        ans[i] = x[i][N + 1];
        for (auto iter = x[i].begin(); iter != x[i].end(); ++iter) {
            if (iter->first == M + 1 || iter->first == i) continue;
            ans[i] -= iter->second * ans[iter->first];
        }
        ans[i] /= x[i][i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> M >> N;
    for (int i = 0; i < 4; ++i) {
        cin >> PR[i];
        PR[i] /= 100;
    }
    for (int i = 0; i < N; ++i) cin >> X[i];

    int MM = 0;
    double base = 0;
    bfs(MM, base);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (Y[i][j] > 0) {
                int P = Y[i][j];
                add(P, P, 1);
                if (i == 0 && X[i][j] == '.') add(P, MM + 1, base);
                for (int k = 0; k < 4; ++k) {
                    int a = i + MX[k], b = j + MY[k];
                    if (inside(a, b) && X[a][b] == '.') {
                        int Q = Y[a][b];
                        add(P, Q, -find(a, b, i, j));
                    }
                }
            }
        }   
    }

    gauss(MM);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (X[i][j] == 'T') cout << fixed << setprecision(9) << ans[Y[i][j]] << endl;
        }
    }

    return 0;
}
