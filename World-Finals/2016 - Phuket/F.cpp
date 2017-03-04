#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;

struct state {
    int cnt;
    long long L;
    state(): L(0), cnt(0) {}
};

string name[MAXN];
int X[MAXN], ans[MAXN];
long long L[MAXN], LL[MAXN];
vector<pair<int, long long> > Y[MAXN];
state S[MAXN];

void dfs(int a, long long P) {
    if (Y[a].size() == 0) LL[a] = P;
    for (int i = 0; i < Y[a].size(); ++i) dfs(Y[a][i].first, P + Y[a][i].second);
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> name[i] >> X[i] >> L[i];
        X[i] = X[i] == 0 ? 0 : X[i] + N;
        Y[X[i]].push_back(make_pair(i, L[i]));
    }
    for (int i = 1; i <= M; ++i) {
        cin >> X[N + i] >> L[N + i];
        X[N + i] = X[N + i] == 0 ? 0 : X[N + i] + N;
        Y[X[N + i]].push_back(make_pair(N + i, L[N + i]));
    }
    dfs(0, 0);

    multiset<pair<long long, int> > C;
    for (int i = 1; i <= N; ++i) C.insert(make_pair(L[i], X[i]));

    vector<pair<long long, int> > XX;
    for (int i = 1; i <= N; ++i) XX.push_back(make_pair(LL[i], i));
    sort(XX.begin(), XX.end());

    int count = N;
    for (int i = 0; i < XX.size(); ++i) {
        while (!C.empty()) {
            if (C.begin()->first <= XX[i].first) {
                --count;
                long long nextL = C.begin()->first;
                int P = C.begin()->second;
                C.erase(C.begin());
                ++S[P].cnt;
                if (S[P].L == 0) 
                    S[P].L = nextL; 
                else
                    S[P].L = min(S[P].L, nextL);
                if (P != 0 && S[P].cnt == Y[P].size()) {
                    C.insert(make_pair(S[P].L + L[P], X[P]));
                    ++count;
                }
            } else {
                break;
            }
        }
        ans[XX[i].second] = count + 1;
    }
    for (int i = 1; i <= N; ++i) cout << name[i] << " " << ans[i] << endl;

    return 0;
}
