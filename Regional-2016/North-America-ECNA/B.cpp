#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

deque<string> P;
string BO, BD, WO, WD;
int BOT, BDT, WOT, WDT;
unordered_map<string, int> C;
int maxN = 0;
vector<string> SS[1000];

int main() {
    int N, j = 0;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string PP;
        cin >> PP;
        P.push_back(PP);
    }
    string Q;
    cin >> Q;
    WO = P[0]; WOT = 0;
    BO = P[1]; BOT = 1;
    WD = P[2]; WDT = 2;
    BD = P[3]; BDT = 3;
    P.pop_front();
    P.pop_front();
    P.pop_front();
    P.pop_front();
    for (int i = 0; i < Q.size(); ++i) {
        if (Q[i] == 'W') {
            string NN;
            if (WOT < WDT) {
                NN = WO + " " + WD;
            } else {
                NN = WD + " " + WO;
            }
            ++C[NN];
            if (C[NN] > maxN) maxN = C[NN];
            SS[C[NN]].push_back(NN);

            if (BOT < BDT) {
                NN = BO + " " + BD;
            } else {
                NN = BD + " " + BO;
            }
            C[NN] = 0;

            swap(WO, WD);
            swap(WOT, WDT);
            swap(BOT, BDT);
            P.push_back(BD);
            BD = BO; 
            BO = P[0]; BOT = 4 + i;
            P.pop_front();
        } else {
            string NN;
            if (BOT < BDT) {
                NN = BO + " " + BD;
            } else {
                NN = BD + " " + BO;
            }
            ++C[NN];
            if (C[NN] > maxN) maxN = C[NN];
            SS[C[NN]].push_back(NN);

            if (WOT < WDT) {
                NN = WO + " " + WD;
            } else {
                NN = WD + " " + WO;
            }
            C[NN] = 0;

            swap(BO, BD);
            swap(WOT, WDT);
            swap(BOT, BDT);
            P.push_back(WD);
            WD = WO;
            WO = P[0]; WOT = 4 + i;
            P.pop_front();
        }
    }

    for (int i = 0; i < SS[maxN].size(); ++i) cout << SS[maxN][i] << endl;
    return 0;
}
