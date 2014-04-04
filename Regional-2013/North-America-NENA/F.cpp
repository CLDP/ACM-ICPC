#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 0, 1, 0};
const int MY[4] = {0, 1, 0, -1};
const int MAXN = 20010;
const int INF = 1000000000;

int N, M, nn;
vector<pair<int, int> > x[MAXN];


int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0, now, ans = 0;
    hh[0] = n;
    
    i = s;
    now = INF;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] + 1 == h[i]) {
                flag = true;
                if (p->second < now) now = p->second;
                fa[p->first] = i;
                fi[p->first] = p - x[i].begin();
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
                        p->second -=now;
                        x[tmp].push_back(make_pair(i, now));
                    }
                    now = INF;
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        
        int min = n-1;
        p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] < min) min = h[p->first];
            ++p;
        }
        
        --hh[h[i]];
        if (hh[h[i]] == 0) break;
        h[i] = min + 1;
        ++hh[h[i]];
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}


int getN(int a) {
    if (a <= N) {
        return (a - 1) * M + 1;
    }
    if (a <= N + M) {
        return (N - 1) * M + a - N;
    }
    if (a <= N + M + N) {
        return (N + M + N - a) * N + M;
    }
    return N + M + M + N - a + 1;
}

int markN(int a) {
    if (a <= N) {
        return 1;
    }
    if (a <= N + M) {
        return 2;
    }
    if (a <= N + M + N) {
        return 3;
    }
    return 4;
}

int inside(int a, int b) {
    return a >= 0 && a < N && b >= 0 && b < M;
}

bool dfs(int xs, int ys, int xt, int yt, int D, bool clock, vector<vector<int> > &z) {
    if (z[xs][ys]) return false;
    z[xs][ys] = nn;
    if (xs == xt && ys == yt) return true;
    if (clock) {
        int nextD = (D + 3) % 4;
        int xn = xs + MX[nextD], yn = ys + MY[nextD];
        if (inside(xn, yn) && !z[xn][yn]) D = nextD;
    } else {
        int nextD = (D + 1) % 4;
        int xn = xs + MX[nextD], yn = ys + MY[nextD];
        if (inside(xn, yn) && !z[xn][yn]) D = nextD;
    }
    for (int i = 0; i < 4; ++i) {
        int xn = xs + MX[D], yn = ys + MY[D];
        if (inside(xn, yn) && dfs(xn, yn, xt, yt, D, clock, z)) return true;
        if (clock) D = (D + 1) % 4; else D = (D + 3) % 4;
    }
    
    return false;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        int T;
        cin >> N >> M >> T;
        int s = N * M * 2 + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) x[i].clear();
        for (int i = 1; i <= N * M; ++i) {
            x[i].push_back(make_pair(N * M + i, 1));
        }
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             if (j < M - 1) x[N * M + i * M + j + 1].push_back(make_pair(i * M + j + 2, 1));
             if (j > 0)     x[N * M + i * M + j + 1].push_back(make_pair(i * M + j, 1));
             if (i < N - 1) x[N * M + i * M + j + 1].push_back(make_pair((i + 1) * M + j + 1, 1));
             if (i > 0)     x[N * M + i * M + j + 1].push_back(make_pair((i - 1) * M + j + 1, 1));
         }
        
        int a, b;
        vector<int> A, B;
        for (int i = 0; i < T; ++i) {
            scanf("%d%d", &a, &b);
            if (a > b) swap(a, b);
            A.push_back(a);
            B.push_back(b);
            x[s].push_back(make_pair(getN(a), 1));
            x[getN(b) + N * M].push_back(make_pair(t, 1));
        }
        
        if (max_flow(s, t, t) != T) {
            cout << "NO" << endl;
            continue;
        }
        
        bool flag = true;
        vector<int> cA(T, 0), cB(T, 0);
        queue<int> que;
        
        vector<vector<int> > z(N, vector<int>(M, false));
        vector<bool> cz(T, false);
        
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < T; ++j) {
                if (i == j) continue;
                if (A[i] <= A[j] && A[j] <= B[i]) {
                    if (A[i] <= B[j] && B[j] <= B[i]) {
                        ++cA[i];
                    } else {
                        flag = false;
                        break;
                    }
                } else {
                    if (A[i] <= B[j] && B[j] <= B[i]) {
                        flag = false;
                        break;
                    } else {
                        ++cB[i];
                    }
                }
            }
            if (cA[i] == 0 || cB[i] == 0) {
                cz[i] = true;
                que.push(i);
            }
            if (!flag) break;
        }
        if (!flag) {
            cout << "NO" << endl;
            continue;
        }
        
        nn = 0;
        while (!que.empty()) {
            ++nn;
            int a = que.front();
            que.pop();
            for (int i = 0; i < T; ++i) {
                if (cz[i]) continue;
                if (A[i] <= A[a] && A[a] <= B[i]) {
                    --cA[i];
                } else {
                    --cB[i];
                }
                if (cA[i] == 0 || cB[i] == 0) {
                    que.push(i);
                    cz[i] = true;
                }
            }
            
            int xs = getN(A[a]) - 1, ys = xs % M;
            xs = xs / M;
            int xt = getN(B[a]) - 1, yt = xt % M;
            xt = xt / M;
            int baseD;
            switch (markN(A[a])) {
                case 1 : baseD = 1; break;
                case 2 : baseD = 0; break;
                case 3 : baseD = 3; break;
                case 4 : baseD = 2; break;
            }
            
            if (cA[a] == 0) {
                if (!dfs(xs, ys, xt, yt, baseD, false, z)) {
                    flag = false;
                    break;
                }
            } else {
                if (!dfs(xs, ys, xt, yt, baseD, true, z)) {
                    flag = false;
                    break;
                }
            }
        }
        /*
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) cout << z[i][j] << " ";
            cout << endl;
        }
        */
        
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
