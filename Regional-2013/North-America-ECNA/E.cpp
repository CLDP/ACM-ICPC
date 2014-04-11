#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 500010;
const int INF = 1000000000;
const int MX[5] = {-1, 1, 0, 0, 0};
const int MY[5] = {0, 0, -1, 1, 0};


string X[30];
vector<pair<int, int> > x[MAXN];


int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> fi(n + 1, 0);
    vector<bool> z(n + 1, 0);
    
    int i = 0, now, ans = 0;
    
    i = s;
    now = INF;
    
    while (true) {
        z[i] = true;
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && !z[p->first]) {
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
                    z = vector<bool> (n + 1, false);
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        if (!flag && i == s) break;
        
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}

int inside(int a, int b, int N) {
    return 0 <= a && a < N && 0 <= b && b < N;
}

int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> X[i];
        int L = 0, R = N * N / 2 + 10;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            int s = N * N * 2 * mid + 1, t = s + 1;
            for (int i = 1; i <= t; ++i) x[i].clear();
            int B = N * N;
            for (int i = 0; i < N; ++i)
             for (int j = 0; j < N; ++j) {
                 if (X[i][j] == 'X') continue;
                 int A = i * N + j + 1;
                 for (int k = 0; k < mid; ++k) 
                     x[k * B * 2 + A].push_back(make_pair(k * B * 2 + B + A, 1));
                 for (int l = 0; l < 5; ++l) {
                     if (!inside(i + MX[l], j + MY[l], N)) continue;
                     int C = (i + MX[l]) * N + j + MY[l] + 1;
                     for (int k = 0; k < mid - 1; ++k) 
                         x[k * B * 2 + B + A].push_back(make_pair((k + 1) * B * 2 + C, 1));
                 }
             }
            
            for (int i = 0; i < N; ++i) {
                int A = i * N + 1;
                x[s].push_back(make_pair(A, 1));
                int C = (mid - 1) * B * 2 + B + i * N + N;
                x[C].push_back(make_pair(t, 1));
            }
            if (max_flow(s, t, t) == N) R = mid; else L = mid;
        }
        cout << "Case " << ++times << ": " << R - 1 << endl;
    }
    return 0;
}
