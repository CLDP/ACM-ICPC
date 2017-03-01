#include <iostream>
#include <cstring>
#include <set>
using namespace std;

const int MAXN = 200;

int NN;
int L[MAXN], R[MAXN], S[MAXN], X[MAXN];

void insert(int &t, int a) {
    if (t == 0) {
        t = ++NN;
        ++S[t];
        X[t] = a;
        return ;
    }
    ++S[t];
    if (a > X[t]) insert(R[t], a); else insert(L[t], a);
}

string getS(int root) {
    string ans = to_string(S[root]) + " ";
    if (L[root] != 0) ans = ans + "1 "; else ans = ans + "0 ";
    if (R[root] != 0) ans = ans + "1 "; else ans = ans + "0 ";
    if (L[root] != 0) ans = ans + getS(L[root]);
    if (R[root] != 0) ans = ans + getS(R[root]);
    return ans;
}

int main() {
    int N, M, root;
    cin >> N >> M;
    set<string> C;
    for (int i = 0; i < N; ++i) {
        NN = root = 0;
        memset(L, 0, sizeof(L));
        memset(R, 0, sizeof(R));
        memset(S, 0, sizeof(S));
        memset(X, 0, sizeof(X));
        int a;
        for (int j = 0; j < M; ++j) {
            cin >> a;
            insert(root, a);
        }
        C.insert(getS(root));
    }
    cout << C.size() << endl;
    return 0;
}
