#include <iostream>
using namespace std;

const int MAXN = 52;

bool f[MAXN], z[MAXN][MAXN];


bool dfs(int a) {
    if (f[a]) return true;
    f[a] = true;
    if (a & 1) --a; else ++a;
    for (int i = 0; i < 52; ++i) {
        if (z[a][i]) {
            if (dfs(i)) return true;
        }
    }
    if (a & 1) --a; else ++a;
    f[a] = false;
    return false;
}


int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string p;
        cin >> p;
        string s[4];
        for (int j = 0; j < 4; ++j) s[j] = p.substr(j * 2, 2);
        for (int j = 0; j < 4; ++j) {
            if (s[j] == "00") continue;
            int a = s[j][0] - 'A';
            a = a * 2 + (s[j][1] == '-');
            for (int k = j + 1; k < 4; ++k) {
                if (s[k] == "00") continue;
                int b = s[k][0] - 'A';
                b = b * 2 + (s[k][1] == '-');
                z[a][b] = z[b][a] = true;
            }
        }
    }
    
    for (int i = 0; i < 52; ++i) {
        if (dfs(i)) {
            cout << "unbounded" << endl;
            return 0;
        }
    }
    
    cout << "bounded" << endl;
    return 0;
}
