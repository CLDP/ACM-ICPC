#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    // and 1, or 2, xor 3, not 4
    int type;
    int a, b, c;
};

int N, G, U, B;
node y[50];
int z[50];
int in[50];
int out[50];
int INPUT[1000][30];

int getN(string P) {
    if (P[0] == 'i') {
        return P[1] - '0';
    } else {
        int ans = N;
        if (P.size() == 3) ans += 10 + P[2] - '0'; else ans += P[1] - '0';
        return ans;
    }
}

bool check() {
    int res[50];
    for (int t = 0; t < B; ++t) {
        bool flag =  true;
        for (int i = 0; i < N + G; ++i) {
            int p = z[i];
            if (p <= N) {
                res[p] = INPUT[t][p - 1];
            } else {
                int a = y[p - N].a, b = y[p - N].b;
                switch (y[p - N].type) {
                    case 10 : res[p] = 1; break;
                    case 4  : res[p] = !res[a]; break;
                    case 3  : res[p] = res[a] ^ res[b]; break;
                    case 2  : res[p] = res[a] | res[b]; break;
                    case 1  : res[p] = res[a] & res[b]; break;
                    case -1 : res[p] = !(res[a] & res[b]); break;
                    case -2 : res[p] = !(res[a] | res[b]); break;
                    case -3 : res[p] = !(res[a] ^ res[b]); break;
                    case -4 : res[p] = res[a]; break;
                    case -10: res[p] = 0; break;
                }
            }
        }
        for (int i = 0; i < U; ++i) flag &= (res[N + out[i]] == INPUT[t][N + i]);
        if (!flag) return false;
    }
    return true;
}


int main() {
    int times = 0;
    while (cin >> N >> G >> U) {
        if (N == 0) break;
        memset(in, 0, sizeof(in));
        
        for (int i = 1; i <= G; ++i) {
            char c;
            string p, q;
            cin >> c;
            if (c == 'a') {
                cin >> p >> q;
                y[i].a = getN(p);
                y[i].b = getN(q);
                y[i].c = N + i;
                in[N + i] = 2;
                y[i].type = 1;
            } else
            if (c == 'o') {
                cin >> p >> q;
                y[i].a = getN(p);
                y[i].b = getN(q);
                y[i].c = N + i;
                in[N + i] = 2;
                y[i].type = 2;
            } else
            if (c == 'x') {
                cin >> p >> q;
                y[i].a = getN(p);
                y[i].b = getN(q);
                y[i].c = N + i;
                in[N + i] = 2;
                y[i].type = 3;
            } else {
                cin >> p;
                y[i].a = getN(p);
                y[i].b = -1;
                y[i].c = N + i;
                in[N + i] = 1;
                y[i].type = 4;
            }
        }
        
        vector<bool> Z(N + G + 2, false);
        for (int i = 0; i < N + G; ++i) {
            for (int j = 1; j <= N + G; ++j) {
                if (Z[j]) continue;
                if (in[j] > 0) continue;
                z[i] = j;
                Z[j] = true;
                for (int k = 1; k <= G; ++k) {
                    if (y[k].a == j || y[k].b == j) --in[y[k].c];
                }
                break;
            }
        }
        
        for (int i = 0; i < U; ++i) cin >> out[i];
        
        cin >> B;
        for (int i = 0; i < B; ++i) 
         for (int j = 0; j < N + U; ++j) cin >> INPUT[i][j];
        
        cout << "Case " << ++times << ": ";
        if (check()) {
            cout << "No faults detected" << endl;
            continue;
        }
        
        int ans = 0, a, b;
        
        for (int i = 1; i <= G; ++i) {
            y[i].type = -y[i].type;
            if (check()) {
                ++ans;
                a = i, b = 0;
            }
            int temp = -y[i].type;
            y[i].type = 10;
            if (check()) {
                ++ans;
                a = i, b = 1;
            }
            y[i].type = -10;
            if (check()) {
                ++ans;
                a = i, b = 2;
            }
            y[i].type = temp;
        }
        if (ans == 1) {
            cout << "Gate " << a << " is failing; ";
            switch (b) {
                case 0 : cout << "output inverted" << endl; break;
                case 1 : cout << "output stuck at 1" << endl; break; 
                case 2 : cout << "output stuck at 0" << endl; break;
            }
        } else {
            cout << "Unable to totally classify the failure" << endl;
        }
    }
    return 0;
}
