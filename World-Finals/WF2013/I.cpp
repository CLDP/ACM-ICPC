#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 502;
const int INF = 1000000000;

int A, B, N, M;
int x[MAXN][MAXN], l[MAXN];
long long ans = 0;

int update(int a, int b, int h) {
    long long S = 1LL * a * b;
    long long H = 1LL * h;
    long long SS = 1LL * N * M;
    if (H * SS % (SS - S) == 0) {
        long long D = H * SS / (SS - S) - 1;
        if (D * S > ans) ans = D * S;
    } else {
        long long D = H * SS / (SS - S);
        if (D * S > ans) ans = D * S;
    }
    return 0;
}

int main() {
    cin >> A >> B >> N >> M;
    if (A > B) swap(A, B);
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) cin >> x[i][j];
    
    for (int jl = 1; jl <= M; ++jl) {
        for (int i = 1; i <= N; ++i) l[i] = x[i][jl];
        
        for (int jr = jl; jr <= M; ++jr) {
            if (jr - jl + 1 > B) break;
            for (int i = 1; i <= N; ++i) l[i] = min(l[i], x[i][jr]);
            
            stack<pair<int, int> > S;
            S.push(make_pair(0, 0));
            for (int i = 1; i <= N; ++i) {
                if (S.top().first > l[i]) {
                    int prev = i;
                    while (S.top().first > l[i]) {
                        int a = jr - jl + 1;
                        int b = i - S.top().second;
                        if (a > b) swap(a, b);
                        if (a > A) a = A;
                        if (b > B) b = B; 
                        int h = S.top().first;
                        update(a, b, h);
                        prev = S.top().second;
                        S.pop();
                    }
                    S.push(make_pair(l[i], prev));
                } else {
                    S.push(make_pair(l[i], i));
                }
            }
            
            while (!S.empty()) {
                if (S.top().first > 0) {
                    int a = jr - jl + 1;
                    int b = N + 1 - S.top().second;
                    if (a > b) swap(a, b);
                    if (a > A) a = A;
                    if (b > B) b = B; 
                    int h = S.top().first;
                    update(a, b, h);
                    S.pop();
                } else {
                    break;
                }
            }
        }
    }
    
    cout << ans << endl;

    return 0;
}
