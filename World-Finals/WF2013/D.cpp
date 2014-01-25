#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXP = 16;
const unsigned long long INF = 1ULL << 63;
const int P[MAXP] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

int S[MAXP];
unsigned long long C[63][63];
map<unsigned long long, unsigned long long> ansT;


int update(int pos, unsigned long long num) {
    int N = 0;
    for (int i = 0; i <= pos; ++i) N += S[i];
    unsigned long long ans = 1;
    for (int i = 0; i < pos; ++i) {
        if (C[N][S[i]] >= INF) return 0;
        if (ans >= INF / C[N][S[i]]) return 0;
        ans *= C[N][S[i]];
        N -= S[i];
    }
    if (ansT.find(ans) == ansT.end()) {
        ansT[ans] = num;
    } else {
        if (num < ansT[ans]) ansT[ans] = num;
    }
    return 0;
}


int dfs(unsigned long long temp, int pos, int up) {
    for (int i = 1; i <= up; ++i) {
        if (temp >= INF / P[pos]) break;
        S[pos] = i;
        temp *= P[pos];
        update(pos, temp);
        dfs(temp, pos + 1, i);
    }
    return 0;
}

int main() {
    C[0][0] = 1;
    for (int i = 1; i < 63; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) 
         if (C[i-1][j] < INF && C[i-1][j-1] < INF) {
             C[i][j] = C[i-1][j] + C[i-1][j-1];
         } else {
             C[i][j] = INF;
         }
    }
    dfs(1, 0, 63);
    
    unsigned long long N;
    while (cin >> N) cout << N << " " << ansT[N] << endl;
    
    return 0;
}
