#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100100;

struct node {
    string P;
    vector<int> X;
    int pos;
    bool operator < (const node &B) const {
        if (X != B.X) return X < B.X;
        return pos < B.pos;
    }
};

vector<node> X;
int z[MAXN];

void z_algorithm(const string &s, int n) {
    int L = 0, R = 0;
    for (int i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R]) ++R;
            z[i] = R - L; 
            --R;
        } else {
            int k = i - L;
            if (z[k] < R - i + 1) 
                z[i] = z[k];
            else {
                L = i;
                while (R < n && s[R - L] == s[R]) ++R;
                z[i] = R - L; 
                --R;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        node Z;
        cin >> Z.P;
        Z.pos = i;
        z_algorithm(Z.P, Z.P.size());
        for (int j = 1; j < Z.P.size(); ++j) {
            if (j + z[j] != Z.P.size()) continue;
            if (j + Z.P.size() > N) continue;
            Z.X.push_back(z[j]);
        }
        X.push_back(Z);
    }
    sort(X.begin(), X.end());
    for (int i = 0; i < M; ++i) cout << X[i].P << endl;
    return 0;
}
