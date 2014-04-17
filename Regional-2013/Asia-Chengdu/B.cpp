#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> S;

bool deal(string &P) {
    int N = P.size();
    vector<string> Q;
    for (int i = 0 ; i < N; ++i) {
        if (P[i] == '<') {
            string R;
            while (P[i] != '>') {
                R = R + P[i];
                ++i;
            }
            R = R + P[i];
            Q.push_back(R);
            continue;
        }
        if (P[i] == 32 || P[i] == 9 || P[i] == 10) {
            while (P[i] == 32 || P[i] == 9 || P[i] == 10) ++i;
            --i;
            continue;
        }
        string R;
        while (!(P[i] == 32 || P[i] == 9 || P[i] == 10 || P[i] == '<')) {
            R = R + P[i];
            ++i;
        }
        Q.push_back(R);
        --i;
    }
    
    int k = 0;
    N = Q.size();
    for (int i = 0; i < N; ++i) {
        if (Q[i][0] == '<' && Q[i][1] == '/') --k;
        for (int j = 0; j < k; ++j) cout << " ";
        if (Q[i][0] == '<') {
            cout << Q[i] << endl;
            if (Q[i][1] != '/' && Q[i][Q[i].size() - 2] != '/') ++k;
            continue;
        }
        cout << Q[i];
        ++i;
        while (Q[i][0] != '<') {
            cout << " " << Q[i];
            ++i;
        }
        --i;
        cout << endl;
    }
    
    return 0;
}

int main() {
    int N;
    cin >> N;
    string P;
    int k = 0;
    string Q;
    while (getline(cin, P)) Q = Q + " " + P;
    
    for (int i = 0; i < N; ++i) {
        int l = Q.find("<html>"), r = Q.find("</html>");
        S.push_back(Q.substr(l, r + 7 - l));
        Q.erase(Q.begin(), Q.begin() + r + 7);
    }
    
    for (int i = 0; i < N; ++i) {
        cout << "Case #" << i + 1 << ":" << endl;
        deal(S[i]);
    }
    return 0;
}
