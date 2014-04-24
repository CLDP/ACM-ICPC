#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


long long CC[100];

long long C(char c) {
    if ('a' <= c && c <= 'z') 
        return CC[c - 'a' + 26]; 
    else 
        return CC[c - 'A'];
}


char P[300100];


int main() {
    int N;
    cin >> N >> P;
    long long D = 0, ans = 0;
    map<long long, long long> T;
    CC[0] = 1;
    for (int i = 1; i < 52; ++i) CC[i] = (CC[i - 1] << 1);
    
    T[0] = 1;
    for (int i = 0; i < N; ++i) {
        D ^= C(P[i]);
        ans += T[D];
        for (int j = 0; j < 52; ++j) {
            if (T.find(D ^ CC[j]) == T.end()) continue;
            ans += T[D ^ CC[j]];
        }
        ++T[D];
    }
    cout << ans << endl;
    
    return 0;
}
