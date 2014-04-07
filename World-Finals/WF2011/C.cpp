#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int m[205][205];
bool v[205][205];

bool inside(int a, int b, int N, int M) {
    return a >= 0 && a <= N + 1 && b >= 0 && b <= M + 1;
}

int main() {
    map<char, int> C;
    for (int i = 0; i < 10; ++i) C[i + '0'] = i;
    for (int i = 0; i < 6; ++i) C['a' + i] = i + 10;
    int N, M, times = 0;
    
    while (cin >> N >> M) {
        if (N == 0) break;
        memset(m, 0, sizeof(m));
        memset(v, 0, sizeof(v));
        
        for (int i = 0; i < N; ++i) {
            int j = 1;
            string s;
            cin >> s;
            for (int k = 0; k < M; ++k) {
                int l = C[s[k]];
                int n = j + 3;
                j += 4;
                while (l > 0) {
                    m[i + 1][n] = l % 2;
                    l = l / 2;
                    --n;
                }
            }
        }
        
        int res = 0, tx = 0, ty = 0;
        while (true) {
            while ((m[tx][ty] != 0) || (v[tx][ty])) {
                ++ty;
                if (ty > M * 4 + 1) {
                    ty = 0;
                    ++tx;
                }
                if (tx > N + 1) break;
            }
            if (tx > N + 1) break;
            
            queue<pair<int, int> > que;
            que.push(make_pair(tx, ty));
            v[tx][ty] = true;
            if (++res > 1) m[tx][ty] = res;
            while (!que.empty()) {
                int x = que.front().first;
                int y = que.front().second;
                que.pop();
                for (int i = 0; i < 4; ++i) {
                    int a = x + MX[i], b = y + MY[i];
                    if (inside(a, b, N, M * 4) && m[a][b] == 0 && !v[a][b]) {
                        que.push(make_pair(a, b));
                        if (res > 1) m[a][b] = res;
                        v[a][b] = true;
                    }
                }
            }
        }
        
        tx = ty = 0;
        memset(v, 0, sizeof(v));
        string ans;
        while (true) {
            set<int> S;
            while ((m[tx][ty] == 0) || (v[tx][ty])) {
                ++ty;
                if (ty > M * 4 + 1) {
                    ty = 0;
                    ++tx;
                }
                if (tx > N + 1) break;
            }
            if (tx > N + 1) break;
            
            queue<pair<int, int> > que;
            que.push(make_pair(tx, ty));
            v[tx][ty] = true;
            S.insert(m[tx][ty]);
            ++res;
            while (!que.empty()) {
                int x = que.front().first;
                int y = que.front().second;
                que.pop();
                for (int i = 0; i < 4; ++i) {
                    int a = x + MX[i], b = y + MY[i];
                    if (inside(a, b, N, M * 4) && m[a][b] != 0 && !v[a][b]) {
                        que.push(make_pair(a, b));
                        S.insert(m[a][b]);
                        v[a][b] = true;
                    }
                }
            }
            
            switch (S.size()) {
                case 1 : ans += "W"; break;
                case 2 : ans += "A"; break;
                case 3 : ans += "K"; break;
                case 4 : ans += "J"; break;
                case 5 : ans += "S"; break;
                case 6 : ans += "D"; break;
            }
        }
        
        sort(ans.begin(), ans.end());
        cout << "Case " << ++times << ": " << ans << endl;
    }
    
    return 0;
}
