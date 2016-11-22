#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;

int x[MAXN][MAXN];
vector<int> X[MAXN];
int T[MAXN], f[MAXN];
bool z[MAXN];


bool check(int a, int b) {
    if (X[a].size() == 0) return true;
    
    vector<int> A = X[a], B = X[b];
    for (int i = 0; i < A.size(); ++i) B.push_back(B[i]);
    
    for (int i = 0; i < A.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < A.size(); ++j) {
            if (f[A[j]] != f[B[i + j]]) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        
        for (int j = 0; j < X[a].size(); ++j) {
            int L = X[A[j]].size();
            int p = x[A[j]][a], q = x[B[i + j]][b];
            for (int k = 0; k < L; ++k) {
                if (f[X[A[j]][p]] != f[X[B[i + j]][q]]) {
                    flag = false;
                    break;
                }
                p = (p + 1) % L;
                q = (q + 1) % L;
            }
            if (!flag) break;
        }
        if (!flag) continue;
        return true;
    }
    
    return false;
}

int main() {
    int N, a, b;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        for (int j = 0; j < a; ++j) {
            cin >> b;
            X[i].push_back(b);
            x[i][b] = j;
        }
        f[i] = a;
    }
    
    int M = N;
    
    while (true) {
        bool flag = false;
        memset(z, 0, sizeof(z));
        for (int i = 1; i <= N; ++i) {
            if (z[i]) continue;
            vector<int> C;
            for (int j = i; j <= N; ++j) {
                if (f[j] == f[i]) {
                    z[j] = true;
                    C.push_back(j);
                }
            }
            
            bool temp_flag = false;
            vector<int> NEW;
            vector<vector<int> > SS;
            NEW.push_back(0);
            SS.push_back(vector<int>(1, C[0]));
            
            for (int j = 1; j < C.size(); ++j) {
                bool same = false;
                for (int k = 0; k < NEW.size(); ++k) {
                    int a = NEW[k];
                    if (check(C[a], C[j])) {
                        SS[k].push_back(C[j]);
                        same = true;
                        break;
                    } 
                }
                if (!same) {
                    temp_flag = flag = true;
                    NEW.push_back(j);
                    SS.push_back(vector<int>(1, C[j]));
                }
            }
            
            for (int j = 0; j < SS.size(); ++j) {
                ++M;
                for (int k = 0; k < SS[j].size(); ++k) f[SS[j][k]] = M;
            }
            if (temp_flag) continue;
        }
        
        if (!flag) break;
    }
    
    bool none = true;
    memset(z, 0, sizeof(z));
    for (int i = 1; i <= N; ++i) {
        if (z[i]) continue;
        z[i] = true;
        bool flag = false;
        for (int j = i + 1; j <= N; ++j) {
            if (f[j] != f[i]) continue;
            flag = true;
            break;
        }
        
        if (!flag) continue;
        
        none = false;
        cout << i;
        for (int j = i + 1; j <= N; ++j) {
            if (f[j] != f[i]) continue;
            cout << " " << j;
            z[j] = true;
        }
        cout << endl;
    }
    if (none) cout << "none" << endl;
    
    return 0;
}
