#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

int f[5010];

int main() {
    string P;
    getline(cin, P);
    if (P.size() % 2 == 1) {
        cout << "impossible" << endl;
        return 0;
    }
    
    int N = P.size();
    multiset<int> S, SS;
    for (int i = 0; i < N; ++i) {
        if (P[i] == '(') f[i + 1] = f[i] + 1; else f[i + 1] = f[i] - 1;
        S.insert(f[i + 1]);
    }
    
    if (*S.begin() >= 0 && f[N] == 0) {
        cout << "possible" << endl;
        return 0;
    }
    
    int prev = 0;
    for (int i = 0; i < N; ++i) {
        if (prev < 0) break;
        SS = S;
        
        int temp = prev;
        for (int j = i; j < N; ++j) {
            SS.erase(SS.find(f[j + 1]));
            if (P[j] == '(') --temp; else ++temp;
            
            if (temp < 0) break;
            
            if (temp + f[N] - f[j + 1] != 0) continue;
            
            
            if (j == N - 1) {
                cout << "possible" << endl;
                return 0;
            }
            
            int a = *SS.begin();
            a -= f[j + 1];
            if (a + temp >= 0) {
                cout << "possible" << endl;
                return 0;
            }
        }
        if (P[i] == '(') ++prev; else --prev;
        S.erase(S.find(f[i + 1]));
    }
    
    cout << "impossible" << endl;
    
    return 0;
}
