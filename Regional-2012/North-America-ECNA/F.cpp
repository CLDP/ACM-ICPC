#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int times = 1; times <= T; ++times) {
        int N, W;
        cin >> N >> W;
        string P, Q;
        getline(cin, Q);
        unordered_set<int> S;

        int K = 0, L = 0;
        for (int i = 0; i < N; ++i) {
            getline(cin, P);
            while (true) {
                if (S.find(K + 1) != S.end()) {
                    ++K;
                    continue;
                }
                Q = to_string(K + 1);
                if (P.find(Q) == string::npos) break;
                ++K;
            }
            L = max(L, K);
            for (int i = W; i >= 1; --i) {
                if (S.find(K + i) != S.end()) continue;
                Q = to_string(K + i);
                if (P.find(Q) != string::npos) {
                    S.insert(K + i);
                    L = max(L, K + i);
                }
            }
        }
        cout << "Case " << times << ": " << K << " " << L << endl;
    }
    return 0;
}
