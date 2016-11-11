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

const int MAXN = 1100;

bool z[MAXN], flag;
vector<int> x[MAXN];

int dfs(int a, int b, int T) {
    z[a] = true;
    if (a == T) {
        flag = true;
        return 1;
    }
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == b) continue;
        return dfs(x[a][i], a, T) + 1;
    }
    return 1;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        x[a].push_back(b);
        x[b].push_back(a);
    }
    int T = 1;
    for (int i = 2; i <= N; ++i)
     if (x[i].size() > x[T].size()) T = i;
    
    if (N == K) {
        cout << 0 << endl;
        return 0;
    }
    
    int L = 0, R = N;
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        int ans = 0;
        vector<int> C;
        memset(z, 0, sizeof(z));
        z[T] = true;
        
        for (int i = 0; i < x[T].size(); ++i) {
            if (z[x[T][i]]) continue;
            flag = false;
            int P = dfs(x[T][i], T, T);
            if (!flag) {
                ans += P / (2 * mid + 1);
                if (P % (2 * mid + 1) >= 0) C.push_back(P % (2 * mid + 1));
            } else {
                if (P > 2 * mid + 1) {
                    ans += (P - 1) / (2 * mid + 1);
                    int R = (P - 1) % (2 * mid + 1);
                    if (R / 2 >= 0) C.push_back(R / 2);
                    if (R - R / 2 >= 0) C.push_back(R - R / 2);
                } else {
                    --P;
                    if (P / 2 >= 0) C.push_back(P / 2);
                    if (P - P / 2 >= 0) C.push_back(P - P / 2);
                }
            }
        }
        int P = -1;
        sort(C.rbegin(), C.rend());
        
        for (int i = 0; i < C.size(); ++i) {
            if (C[i] > mid) {
                ++ans;
                P = max(P, mid + mid - C[i]);
            } else {
                if (P < C[i]) ++ans;
                break;
            }
        }
        
        if (ans <= K) R = mid; else L = mid;
    }
    cout << R << endl;
    
    
    return 0;
}
