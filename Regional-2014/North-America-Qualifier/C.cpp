#include <cstdio>
#include <vector>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[1000];

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) cin >> x[i];
    if (x[M] != N) x[++M] = N;
    
    set<int> S;
    int ans = 0;
    for (int i = 0; i <= M; ++i)
     for (int j = i + 1; j <= M; ++j) {
         S.insert(x[j] - x[i]);
     }
    
    for (set<int>::iterator iter = S.begin(); iter != S.end(); ++iter) cout << *iter << " ";
    cout << endl;
    

    return 0;
}
