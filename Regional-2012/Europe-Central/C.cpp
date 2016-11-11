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


string P = "h*helibeb*c*n*o*f*nenamgalsip*s*clark*casctiv*crmnfeconicuzngageassebrkrrbsry*zrnbmotcrurhpdagcdinsnsbtei*xecsbahftaw*reosirptauhgtlpbbipoatrnfrrarfdbsgbhhsmtdsrgcnfllvlaceprndpmsmeugdtbdyhoertmybluacthpau*nppuamcmbkcfesfmmdnolr";

bool f[50010];

int main() {
    int N, M;
    M = P.size();
    
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string Q;
        cin >> Q;
        int K = Q.size();
        for (int j = 0; j <= K; ++j) f[j] = false;
        f[0] = true;
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; k += 2) {
                if (P[k + 1] == '*' && P[k] == Q[j]) {
                    f[j + 1] |= f[j];
                }
                if (P[k + 1] != '*' && j > 0 && P[k] == Q[j - 1] && P[k + 1] == Q[j]) {
                    f[j + 1] |= f[j - 1];
                }
            }
        }
        if (f[K]) cout << "YES" << endl; else cout << "NO" << endl;
    }
    
    return 0;
}
