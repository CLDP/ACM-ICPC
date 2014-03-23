#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    int N;
    bool first = true;
    while (cin >> N) {
        if (N == 0) break;
        if (!first) cout << endl;
        first = false;
        
        string P;
        int A = 0, B = 0, T;
        for (int i = 0; i < N; ++i) {
            cin >> P >> T;
            if (P == "DROP") {
                B += T;
                cout << "DROP 2 " << T << endl;
            } else {
                if (A >= T) {
                    A -= T;
                    cout << "TAKE 1 " << T << endl;
                } else {
                    if (A > 0) cout << "TAKE 1 " << A << endl;
                    T -= A;
                    A = B;
                    B = 0;
                    cout << "MOVE 2->1 " << A << endl;
                    cout << "TAKE 1 " << T << endl;
                    A -= T;
                }
            } 
        }
    }
    return 0;
}
