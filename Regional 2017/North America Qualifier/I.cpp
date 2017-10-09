#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1010;


int x[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int N;
        cin >> N;
        for (int j = 0; j < N; ++j) cin >> x[j];
        for (int j = 1; j < N - 1; ++j) {
            int pre = -1;
            bool flag = true;
            for (int k = 0; k < N; ++k) {
                if (k == j) continue;
                if (x[k] < pre) {
                    flag = false;
                    break;
                }
                pre = x[k];
            }
            if (flag) {
                cout << j + 1 << endl;
                break;
            }
        }
    }

    return 0;
}
