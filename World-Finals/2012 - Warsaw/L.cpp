#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const string CP1 = "Takeover Incorporated";
const string CP2 = "Buyout Limited";


bool simulate(multiset<long long> &A, multiset<long long> &B, bool &turn) {
    long long temp;
    while (true) {
        if (A.empty()) return false;
        if (B.empty()) return true;
        
        if (turn) {
            turn = !turn;
            if (*(--A.end()) > *(--B.end())) {
                B.erase(--B.end());
                continue;
            }
            if (A.size() != 1) {
                temp = *(--A.end());   A.erase(--A.end());
                temp += *(--A.end());  A.erase(--A.end());
                A.insert(temp);
            }
        } else {
            turn = !turn;
            if (*(--A.end()) < *(--B.end())) {
                A.erase(--A.end());
                continue;
            }
            if (B.size() != 1) {
                temp = *(--B.end());   B.erase(--B.end());
                temp += *(--B.end());  B.erase(--B.end());
                B.insert(temp);
            }
        }
    }
}


int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        multiset<long long> A, B, C, D;
        long long temp;
        for (int i = 0; i < N; ++i) {
            cin >> temp;
            A.insert(temp);
        }
        for (int i = 0; i < M; ++i) {
            cin >> temp;
            B.insert(temp);
        }
        C = A;
        D = B;
        
        ++times;
        bool turn = true;
        bool ans1 = simulate(A, B, turn), ans2 = false;
        turn = false;
        if (C.size() > 1) {
             temp = *(--C.end());   C.erase(--C.end());
             temp += *(--C.end());  C.erase(--C.end());
             C.insert(temp);
             ans2 = simulate(C, D, turn);
        }
        
        cout << "Case " << times << ": ";
        if (ans1 || ans2) cout << CP1 << endl; else cout << CP2 << endl;
    }
    return 0;
}
