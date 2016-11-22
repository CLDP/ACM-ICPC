#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

struct packet {
    int mn, st, end;
};

int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        
        int ms[6];
        vector<int> S;
        int res = 0;
        
        for (int i = 1; i <= N; ++i) {
            S.push_back(i);
            cin >> ms[i];
            res += ms[i];
        }
        
        vector<packet> p(M);
        for (int i = 0; i < M; ++i) cin >> p[i].mn >> p[i].st >> p[i].end;
        
        do {
            int cm = S[0], cmi = 0, cml = 0;
            int worst = 0, cur = 0;
            map<int, int> ex[7];
            
            for (int i = 0; i < M; ++i) {
                if (p[i].mn != cm) {
                    ex[p[i].mn][p[i].st] = p[i].end;
                    cur += p[i].end - p[i].st + 1;
                } else 
                if (p[i].st > cml + 1) {
                    ex[p[i].mn][p[i].st] = p[i].end;
                    cur += p[i].end - p[i].st + 1;
                } else {
                    cml = p[i].end;
                    if (cml == ms[cm]) {
                        ++cmi;
                        if (cmi < N) {
                            cm = S[cmi];
                            cml = 0;
                        }
                    }
                    
                    while ((ex[cm].find(cml + 1) != ex[cm].end()) && (cmi < N)) {
                        int newend = ex[cm][cml + 1];
                        cur = cur - (newend - cml);
                        cml = newend;
                        if (cml == ms[cm])  {
                            ++cmi;
                            if (cmi < N) {
                                cm = S[cmi];
                                cml = 0;
                            }
                        }
                    }
                }
                
                worst = max(worst, cur);
            }
            
            if (worst < res) res = worst;
        } while (next_permutation(S.begin(), S.end()));
        
        cout << "Case " << ++times << ": " << res << endl << endl;
    }
    
    return 0;
}
