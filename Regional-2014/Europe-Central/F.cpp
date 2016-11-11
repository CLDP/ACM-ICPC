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

long long f[1000005][2][2];
char s[3][1000005];

const long long p = 1000000009;

void solve11(int x) {
    int cnt = 1;
    for (int i = 0; i < 3; ++i)
        if (s[i][x] == '?') cnt *= 26;
    f[x + 1][1][1] = (f[x + 1][1][1] + f[x][1][1] * cnt) % p;
}

void solve10(int x) {
    int cnt = (s[0][x] == '?') ? 26 : 1;
    if (s[1][x] == '?') {
        if (s[2][x] == '?') {
            f[x+1][1][0] = (f[x+1][1][0] + f[x][1][0] * cnt * 26) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][1][0] * cnt * 13 * 25) % p;
        } else {
            f[x+1][1][0] = (f[x+1][1][0] + f[x][1][0] * cnt) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][1][0] * cnt * (s[2][x] - 'a')) % p;
        }
    } else {
        if (s[2][x] == '?') {
            f[x+1][1][0] = (f[x+1][1][0] + f[x][1][0] * cnt) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][1][0] * cnt * ('z' - s[1][x])) % p;
        } else 
        if (s[1][x] == s[2][x])
            f[x+1][1][0] = (f[x+1][1][0] + f[x][1][0] * cnt) % p;
        else 
        if (s[1][x] < s[2][x])
            f[x+1][1][1] = (f[x+1][1][1] + f[x][1][0] * cnt) % p;
        else
            cerr << "should not happen 10" << endl;
    }
}

void solve01(int x) {
    int cnt = (s[2][x] == '?') ? 26 : 1;
    if (s[0][x] == '?') {
        if (s[1][x] == '?') {
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][1] * cnt * 26) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][1] * cnt * 13 * 25) % p;
        } else {
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][1] * cnt) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][1] * cnt * (s[1][x] - 'a')) % p;
        }
    } else {
        if (s[1][x] == '?') {
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][1] * cnt) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][1] * cnt * ('z' - s[0][x])) % p;
        } else 
        if (s[0][x] == s[1][x])
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][1] * cnt) % p;
        else 
        if (s[0][x] < s[1][x])
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][1] * cnt) % p;
        else
            cerr << "should not happen 01" << endl;
    }
}

void solve00(int x) {
    if (s[1][x] == '?') {
        if ((s[0][x] == '?') && (s[2][x] == '?')) {
            f[x+1][0][0] = (f[x+1][0][0] + f[x][0][0] * 26) % p;
            f[x+1][1][0] = (f[x+1][1][0] + f[x][0][0] * 13 * 25) % p;
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][0] * 13 * 25) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][0] * 13 * 25 * 8) % p;
        } else 
        if (s[0][x] == '?') {
            f[x+1][0][0] = (f[x+1][0][0] + f[x][0][0]) % p;
            f[x+1][1][0] = (f[x+1][1][0] + f[x][0][0] * (s[2][x] - 'a')) % p;
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][0] * (s[2][x] - 'a')) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][0] * (s[2][x] - 'a') * (s[2][x] - 'a' - 1) / 2) % p;
        } else 
        if (s[2][x] == '?') {
            f[x+1][0][0] = (f[x+1][0][0] + f[x][0][0]) % p;
            f[x+1][1][0] = (f[x+1][1][0] + f[x][0][0] * ('z' - s[0][x])) % p;
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][0] * ('z' - s[0][x])) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][0] * ('z' - s[0][x]) * ('y' - s[0][x]) / 2) % p;
        } else 
        if (s[0][x] == s[2][x]) {
            f[x+1][0][0] = (f[x+1][0][0] + f[x][0][0]) % p;
        } else 
        if (s[0][x] < s[2][x]) {
            f[x+1][0][1] = (f[x+1][0][1] + f[x][0][0]) % p;
            f[x+1][1][0] = (f[x+1][1][0] + f[x][0][0]) % p;
            f[x+1][1][1] = (f[x+1][1][1] + f[x][0][0] * (s[2][x] - s[0][x] - 1)) % p;
        }
    } else {
        int cnt01_0 = 0, cnt01_1 = 0, cnt12_0 = 0, cnt12_1 = 0;
        if (s[0][x] == '?') {
            cnt01_0 = 1;
            cnt01_1 = s[1][x] - 'a';
        } else 
        if (s[0][x] == s[1][x])
            cnt01_0 = 1;
        else 
        if (s[0][x] < s[1][x])
            cnt01_1 = 1;
        else
            cerr << "should not happen 00 **|" << endl;
        
        if (s[2][x] == '?') {
            cnt12_0 = 1;
            cnt12_1 = 'z' - s[1][x];
        } else 
        if (s[2][x] == s[1][x])
            cnt12_0 = 1;
        else 
        if (s[2][x] > s[1][x])
            cnt12_1 = 1;
        else
            cerr << "should not happen 00 |**" << endl;
        
        f[x+1][0][0] = (f[x+1][0][0] + f[x][0][0] * cnt01_0 * cnt12_0) % p;
        f[x+1][0][1] = (f[x+1][0][1] + f[x][0][0] * cnt01_0 * cnt12_1) % p;
        f[x+1][1][0] = (f[x+1][1][0] + f[x][0][0] * cnt01_1 * cnt12_0) % p;
        f[x+1][1][1] = (f[x+1][1][1] + f[x][0][0] * cnt01_1 * cnt12_1) % p;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < 3; ++i) scanf("%s", s[i]);
        memset(f, 0, sizeof(f));
        f[0][0][0] = 1;
        int l = 0;
        int ll[3];
        for (int i = 0; i < 3; ++i) {
            ll[i] = strlen(s[i]);
            l = max(l, ll[i]);
        }
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < 3; ++j)
             if (i >= ll[j]) s[j][i] = '\0';
            solve11(i);
            bool f0 = true, f1 = true;
            if ((s[0][i] != '?') && (s[1][i] != '?') && (s[0][i] > s[1][i])) f0 = false;
            if ((s[1][i] != '?') && (s[2][i] != '?') && (s[1][i] > s[2][i])) f1 = false;
            if (f0 && f1) solve00(i);
            if (f0) solve01(i);
            if (f1) solve10(i);
        }
        
        int res = f[l][1][1];
        printf("%d\n", res);
    }

    return 0;
}
