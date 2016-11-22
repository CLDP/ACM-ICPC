#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const string ORDER[3] = {"Pre", "In", "Post"};

struct node {
    string p[3];
    
    node() {
        p[0] = p[1] = p[2] = "";
    }
    
    node operator = (node const &Q) {
        for (int i = 0; i < 3; ++i)
         if (Q.p[i] != "") p[i] = Q.p[i];
        return *this;
    }
    
    bool operator < (node const &Q) {
        if (Q.p[0] == "") return true;
        if (p[0] != Q.p[0]) return p[0] < Q.p[0];
        return p[1] < Q.p[1];
    }
    
    bool operator == (node const &Q) {
        for (int i = 0; i < 3; ++i) {
            if (p[i] == "" || Q.p[i] == "") continue;
            if (p[i] != Q.p[i]) return false;
        }
        return true;
    }
};


int C[6];
map<string, node> ANS;


bool dfs(node P, node &Q) {
    int lenP = max(P.p[0].size(), max(P.p[1].size(), P.p[2].size()));
    if (lenP == 1) {
        string temp;
        for (int i = 0; i < 3; ++i) {
            if (temp != "" && P.p[i] != "" && temp != P.p[i]) return false;
            if (temp == "") temp = P.p[i];
        }
        Q.p[0] = Q.p[1] = Q.p[2] = temp;
        return true;
    }
    
    if (lenP == 0) return true;
    
    string hash;
    for (int i = 0; i < 3; ++i)
     if (P.p[i] == "") hash = hash + string(lenP, ' '); else hash = hash + P.p[i];
    
    if (ANS.find(hash) != ANS.end()) {
        Q = ANS[hash];
        return Q.p[0] != "";
    }
    
    
    if (P.p[0] != "" && P.p[1] == "" && P.p[2] == "") {
        // Only know pre-order
        for (int i = 0; i < lenP; ++i) {
            node L, R, TL, TR;
            L.p[C[0]] = P.p[0].substr(1, i);
            R.p[C[1]] = P.p[0].substr(i + 1, lenP - i - 1);
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[0][0] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[0][0] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[0][0];
                if (temp < Q) Q = temp;
            }
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    if (P.p[0] == "" && P.p[1] != "" && P.p[2] == "") {
        // Only know in-order
        for (int i = 0; i < lenP; ++i) {
            node L, R, TL, TR;
            L.p[C[2]] = P.p[1].substr(0, i);
            R.p[C[3]] = P.p[1].substr(i + 1, lenP - i - 1);
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[1][i] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[1][i] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[1][i];
                if (temp < Q) Q = temp;
            }
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    if (P.p[0] == "" && P.p[1] == "" && P.p[2] != "") {
        // Only know post-order
        for (int i = 0; i < lenP; ++i) {
            node L, R, TL, TR;
            L.p[C[4]] = P.p[2].substr(0, i);
            R.p[C[5]] = P.p[2].substr(i, lenP - i - 1);
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[2][lenP - 1] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[2][lenP - 1] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[2][lenP - 1];
                if (temp < Q) Q = temp;
            }
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    
    if (P.p[0] != "" && P.p[1] != "" && P.p[2] == "") {
        // Only know pre-order and in-order
        for (int i = 0; i < lenP; ++i) {
            if (P.p[1][i] != P.p[0][0]) continue;
            node L, R, TL, TR;
            L.p[C[2]] = P.p[1].substr(0, i);
            R.p[C[3]] = P.p[1].substr(i + 1, lenP - i - 1);
            
            node L2, R2;
            L2.p[C[0]] = P.p[0].substr(1, i);
            R2.p[C[1]] = P.p[0].substr(i + 1, lenP - i - 1);
            if (!(L == L2 && R == R2)) break;
            L = L2;
            R = R2;
            
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[1][i] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[1][i] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[1][i];
                if (temp < Q) Q = temp;
            }
            // Only run for one time
            break;
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    if (P.p[0] == "" && P.p[1] != "" && P.p[2] != "") {
        // Only know post-order and in-order
        for (int i = 0; i < lenP; ++i) {
            if (P.p[1][i] != P.p[2][lenP - 1]) continue;
            node L, R, TL, TR;
            L.p[C[2]] = P.p[1].substr(0, i);
            R.p[C[3]] = P.p[1].substr(i + 1, lenP - i - 1);
            
            node L2, R2;
            L2.p[C[4]] = P.p[2].substr(0, i);
            R2.p[C[5]] = P.p[2].substr(i, lenP - i - 1);
            if (!(L == L2 && R == R2)) break;
            L = L2;
            R = R2;
            
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[1][i] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[1][i] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[1][i];
                if (temp < Q) Q = temp;
            }
            // Only run for one time
            break;
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    if (P.p[0] != "" && P.p[1] == "" && P.p[2] != "") {
        // Only know pre-order and post-order
        if (P.p[0][0] != P.p[2][lenP - 1]) {
            ANS[hash] = Q;
            return false;
        }
        
        for (int i = 0; i < lenP; ++i) {
            node L, R, TL, TR;
            L.p[C[0]] = P.p[0].substr(1, i);
            R.p[C[1]] = P.p[0].substr(i + 1, lenP - i - 1);
            
            node L2, R2;
            L2.p[C[4]] = P.p[2].substr(0, i);
            R2.p[C[5]] = P.p[2].substr(i, lenP - i - 1);
            if (!(L == L2 && R == R2)) continue;
            L = L2;
            R = R2;
            
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[0][0] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[0][0] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[0][0];
                if (temp < Q) Q = temp;
            }
            // This can run many times!!
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
    
    
    if (P.p[0] != "" && P.p[1] != "" && P.p[2] != "") {
        // know all
        if (P.p[0][0] != P.p[2][lenP - 1]) {
            ANS[hash] = Q;
            return false;
        }
        
        for (int i = 0; i < lenP; ++i) {
            if (P.p[1][i] != P.p[0][0]) continue;
            node L, R, TL, TR;
            L.p[C[2]] = P.p[1].substr(0, i);
            R.p[C[3]] = P.p[1].substr(i + 1, lenP - i - 1);
            
            
            node L2, R2, L3, R3;
            L2.p[C[0]] = P.p[0].substr(1, i);
            R2.p[C[1]] = P.p[0].substr(i + 1, lenP - i - 1);
            L3.p[C[4]] = P.p[2].substr(0, i);
            R3.p[C[5]] = P.p[2].substr(i, lenP - i - 1);
            if (!(L == L2 && R == R2)) break;
            L = L2;
            R = R2;
            if (!(L == L3 && R == R3)) break;
            L = L3;
            R = R3;
            
            if (dfs(L, TL) && dfs(R, TR)) {
                node temp;
                temp.p[0] = P.p[1][i] + TL.p[0] + TR.p[0];
                temp.p[1] = TL.p[1] + P.p[1][i] + TR.p[1];
                temp.p[2] = TL.p[2] + TR.p[2] + P.p[1][i];
                if (temp < Q) Q = temp;
            }
            // Only run for one time
            break;
        }
        ANS[hash] = Q;
        return Q.p[0] != "";
    }
}


int main() {
    node P;
    cin >> P.p[0] >> P.p[1] >> P.p[2];
    for (int i = 0; i < 6; ++i) C[i] = i / 2;
    
    bool flag = false;
    while (C[0] == 0 || flag) {
        node Q;
        if (dfs(P, Q)) {
            for (int i = 0; i < 6; ++i) {
                cout << ORDER[C[i]];
                if (i != 5) cout << " "; else cout << endl;
            }
            cout << Q.p[0] << endl;
            cout << Q.p[1] << endl;
            cout << Q.p[2] << endl;
        }
        
        next_permutation(C, C + 6);
        if (C[0] != 0) flag = true;
        if (C[0] == 0 && flag) break;
        ANS.clear();
    }
    
    return 0;
}
