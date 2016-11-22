#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct Ring {
    vector<int> Rings, Keys;
    int A, B;
};


Ring R[26];
int KP[26];      // Key position
bool x[26][26];
bool KE[26];     // Key Exist
bool RE[26];     // Ring Exist
vector<int> KH;  // Key hash
vector<int> KHO; // Key hash opposite


int add_input(string p) {
    if (p[1] >= 'A' && p[1] <= 'Z') swap(p[0], p[1]);
    RE[p[1] - 'a'] = true;
    if (p[0] >= 'a' && p[0] <= 'z') {
        // Ring - Ring connection
        int R0 = p[0] - 'a', R1 = p[1] - 'a';
        x[R1][R0] = x[R0][R1] = true;
        RE[R0] = true;
        R[R0].Rings.push_back(R1);
        R[R1].Rings.push_back(R0);
    } else {
        // Ring - Key connection
        int R1 = p[1] - 'a', K0 = p[0] - 'A';
        if (K0 < 13) ++R[R1].A; else ++R[R1].B;
        KE[K0] = true;
        KP[K0] = R1;
        R[R1].Keys.push_back(K0);
    }
    return 0;
}


int dp(int a, int fa, vector<bool> &AB, vector<bool> &Z, vector<pair<int, int> > &F, vector<pair<bool, bool> > &CZ) {
    if (fa != -1) {
        if (AB[a] != AB[fa] && CZ[a].first) return F[a].first;
        if (AB[a] == AB[fa] && CZ[a].second) return F[a].second; 
    }
    
    int ans = 0;
    if (!Z[a]) {
        for (int i = 0; i < R[a].Rings.size(); ++i) {
            if (R[a].Rings[i] == fa) continue;
            ans += dp(R[a].Rings[i], a, AB, Z, F, CZ);
        }
        if (fa != -1) {
            ans += AB[a] != AB[fa];
            if (AB[a] != AB[fa]) {
                // different first
                CZ[a].first = true;
                F[a].first = ans;
            } else {
                CZ[a].second = true;
                F[a].second = ans;
            }
        }
    } else {
        int ans1 = 0, ans2 = 0;
        AB[a] = false;
        for (int i = 0; i < R[a].Rings.size(); ++i) {
            if (R[a].Rings[i] == fa) continue;
            ans1 += dp(R[a].Rings[i], a, AB, Z, F, CZ);
        }
        if (fa != -1) ans1 += AB[a] != AB[fa];
        
        AB[a] = true;
        for (int i = 0; i < R[a].Rings.size(); ++i) {
            if (R[a].Rings[i] == fa) continue;
            ans2 += dp(R[a].Rings[i], a, AB, Z, F, CZ);
        }
        if (fa != -1) ans2 += AB[a] != AB[fa];
        
        ans = min(ans1, ans2);
        if (fa != -1) {
            if (AB[a] != AB[fa]) {
                // different first
                CZ[a].first = true;
                F[a].first = ans;
            } else {
                CZ[a].second = true;
                F[a].second = ans;
            }
        }
    }
    return ans;
}


int deal(int a, int mark) {
    vector<int> this_ring;
    vector<bool> AB(26, false);
    vector<bool> Z(26, false);
    
    int NA = 0, NB = 0;
    for (int i = 0; i < 26; ++i) {
        if (!RE[i]) continue;
        if (x[i][a]) {
            if (R[i].A == 0 && R[i].B == 0) {
                this_ring.push_back(i);
                Z[i] = true;
            }
            if (R[i].A > 0) AB[i] = true;
            if (R[i].A > 0) ++NA;
            if (R[i].B > 0) ++NB;
        }
    }
    
    if ((NA == 0 || NB == 0) && mark == 0) return 0;
    if (mark == 1 && NB == 0) return 0;
    if (mark == 2 && NA == 0) return 0;
    
    int N = this_ring.size(), ans = INF;
    
    vector<pair<int, int> > F(26, make_pair(0, 0));
    vector<pair<bool, bool> > CZ(26, make_pair(false, false));
    
    if (mark == 0) return dp(a, -1, AB, Z, F, CZ) * 2 - 1;
    if (mark == 1 || mark == 2) {
        for (int i = 0; i < N; ++i) {
            Z[this_ring[i]] = false;
            AB[this_ring[i]] = mark == 1;
            int temp = dp(a, -1, AB, Z, F, CZ);
            if (temp < ans) ans = temp;
            Z[this_ring[i]] = true;
            F = vector<pair<int, int> >(26, make_pair(0, 0));
            CZ = vector<pair<bool, bool> >(26, make_pair(false, false));
        }
        return ans * 2 - 1;
    }
    
    for (int i = 0; i < N; ++i) {
        Z[this_ring[i]] = false;
        AB[this_ring[i]] = true;
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            Z[this_ring[j]] = false;
            AB[this_ring[j]] = false;
            int temp = dp(a, -1, AB, Z, F, CZ);
            if (temp < ans) ans = temp;
            Z[this_ring[j]] = true;
            F = vector<pair<int, int> >(26, make_pair(0, 0));
            CZ = vector<pair<bool, bool> >(26, make_pair(false, false));
        }
        Z[this_ring[i]] = true;
    }
    return ans * 2 - 1;
}


int try_keys(int a, int &ans, vector<bool> &f, int S) {
    if (a == 26) {
        bool all_same = true, existA = false, existB = false, empty_ring = false;
        for (int i = 0; i < 26; ++i) {
            if (!RE[i]) continue;
            if (R[i].A != 0 && R[i].B != 0) all_same = false;
            if (R[i].A == 0 && R[i].B == 0) empty_ring = true;
            if (R[i].A > 0) existA = true;
            if (R[i].B > 0) existB = true;
        }
        
        if (all_same && (empty_ring || (existA && existB))) {
            f[S] = true;
            if (__builtin_popcount(S) < ans) ans = __builtin_popcount(S);
        }
        return 0;
    }
    
    if (R[a].A == 0 || R[a].B == 0) try_keys(a + 1, ans, f, S);
    
    if (R[a].A > 0) {
        int tempA = R[a].A, SS = 0;
        R[a].A = 0;
        for (int i = 0; i < R[a].Keys.size(); ++i) 
         if (R[a].Keys[i] < 13) SS += (1 << KHO[R[a].Keys[i]]);
         
        try_keys(a + 1, ans, f, S + SS);
        
        R[a].A = tempA;
    }
    
    if (R[a].B > 0) {
        int tempB = R[a].B, SS = 0;
        R[a].B = 0;
        for (int i = 0; i < R[a].Keys.size(); ++i) 
         if (R[a].Keys[i] >= 13) SS += (1 << KHO[R[a].Keys[i]]);
         
        try_keys(a + 1, ans, f, S + SS);
        
        R[a].B = tempB;
    }
    
    if (R[a].A > 0 && R[a].B > 0) {
        int tempA = R[a].A, tempB = R[a].B, SS = 0;
        R[a].A = R[a].B = 0;
        for (int i = 0; i < R[a].Keys.size(); ++i) SS += (1 << KHO[R[a].Keys[i]]);
        
        try_keys(a + 1, ans, f, S + SS);
        
        R[a].A = tempA; R[a].B = tempB;
    }
    
    return 0;
}


int main() {
    int times = 0;
    string p;
    while (cin >> p) {
        memset(x, 0, sizeof(x));
        memset(KE, 0, sizeof(KE));
        memset(RE, 0, sizeof(RE));
        memset(KP, 0, sizeof(KP));
        
        for (int i = 0; i < 26; ++i) {
            R[i].A = R[i].B = 0;
            R[i].Rings.clear();
            R[i].Keys.clear();
        }
        
        ++times;
        add_input(p);
        while (cin >> p) {
            if (p == "0") break;
            add_input(p);
        }
        
        int AN = 0, BN = 0, RN = 0;
        for (int i = 0; i < 26; ++i) {
            if (RE[i]) ++RN;
            if (KE[i]) {
                if (i < 13) ++AN; else ++BN;
            }
        }
        
        if (RN == 1) {
            // Only one ring
            if (AN > 0 && BN > 0) {
                cout << "Case " << times << ": impossible" << endl;
            } else {
                cout << "Case " << times << ": 0 0" << endl;
            }
            continue;
        }
        
        for (int k = 0; k < 26; ++k)
         for (int i = 0; i < 26; ++i)
          for (int j = 0; j < 26; ++j)
           if (x[i][k] && x[k][j]) x[i][j] = true;
        
        if (AN == 0 || BN == 0) {
            // Only one kind of key
            // Need to find out how many parts contains at least one key
            vector<bool> Z(26, false);
            int ans = 0;
            for (int i = 0; i < 26; ++i) {
                if (!RE[i] || Z[i]) continue;
                int temp = R[i].A + R[i].B;
                
                for (int j = i + 1; j < 26; ++j) {
                    if (!x[i][j]) continue;
                    Z[j] = true;
                    temp += R[j].A + R[j].B;
                }
                
                if (temp > 0) ++ans;
            }
            
            // Need ans - 1 connections if possible
            if (ans > 0) --ans;
            
            cout << "Case " << times << ": 0 " << ans << endl;
            continue;
        }
        
        KH.clear();
        KHO = vector<int>(26, 0);
        for (int i = 0; i < 26; ++i)
         if (KE[i]) {
             KH.push_back(i);
             KHO[i] = KH.size() - 1;
         }
        
        int NUM = KH.size();
        vector<bool> f(1 << NUM, false);
        int ans1 = INF;
        
        try_keys(0, ans1, f, 0);
        
        cout << "Case " << times << ": " << ans1 * 2 << " ";
        
        int ans2 = INF;
        for (int S = 0; S < (1 << NUM); ++S) {
            if (__builtin_popcount(S) != ans1 || !f[S]) continue;
            int numA = 0, numB = 0, temp2 = 0;
            
            // Get off useless keys
            for (int i = 0; i < NUM; ++i) {
                if ((S & (1 << i)) == 0) continue;
                if (KH[i] < 13) --R[KP[KH[i]]].A; else --R[KP[KH[i]]].B;
            }
            
            vector<bool> Z(26, false);
            vector<int> ANS(26, 0);
            for (int i = 0; i < 26; ++i) {
                if (!RE[i] || Z[i]) continue;
                temp2 += (ANS[i] = deal(i, 0));
                int SA = R[i].A, SB = R[i].B;
                
                for (int j = i + 1; j < 26; ++j) {
                    if (!x[i][j]) continue;
                    Z[j] = true;
                    SA += R[j].A;
                    SB += R[j].B;
                }
                
                if (SA > 0) ++numA;
                if (SB > 0) ++numB;
            }
            
            if (numA > 0) --numA;
            if (numB > 0) --numB;
            
            temp2 += numA + numB;
            
            bool all_same = true, existA = false, existB = false, empty_ring = false;
            for (int i = 0; i < 26; ++i) {
                if (!RE[i]) continue;
                if (R[i].A != 0 && R[i].B != 0) all_same = false;
                if (R[i].A == 0 && R[i].B == 0) empty_ring = true;
                if (R[i].A > 0) existA = true;
                if (R[i].B > 0) existB = true;
            }
            
            int mark = 0;
            if (!existA) mark += 1;
            if (!existB) mark += 2;
            
            if (mark != 0) {
                int prev_temp = temp2;
                temp2 = INF;
                Z = vector<bool>(26, false);
                for (int i = 0; i < 26; ++i) {
                    if (!RE[i] || Z[i]) continue;
                    
                    int temp3 = prev_temp + deal(i, mark) - ANS[i];
                    
                    for (int j = i + 1; j < 26; ++j) {
                        if (!x[i][j]) continue;
                        Z[j] = true;
                    }
                    if (temp3 < temp2) temp2 = temp3;
                }
            }
            
            // Put on useless keys
            for (int i = 0; i < NUM; ++i) {
                if ((S & (1 << i)) == 0) continue;
                if (KH[i] < 13) ++R[KP[KH[i]]].A; else ++R[KP[KH[i]]].B;
            }
            
            if (temp2 < ans2) ans2 = temp2;
        }
        
        cout << ans2 << endl;
    }

    return 0;
}
