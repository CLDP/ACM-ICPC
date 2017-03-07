#include <iostream>
#include <vector>
using namespace std;

vector<int> X[8];
vector<int> Y[8];

void deal(int B, int N) {
    if (N < 8) {
        for (int i = 0; i < N; ++i) {
            cout << B + X[N][i] << " to " << B + Y[N][i] << endl;
        }
        return ;
    }
    cout << B + N + N - 2 << " to " << B - 1 << endl;
    cout << B + 3 << " to " << B + N + N - 2 << endl;
    deal(B + 4, N - 4);
    cout << B << " to " << B + N + N - 5 << endl;
    cout << B + N + N - 1 << " to " << B << endl;
}

int main() {
    X[3] = vector<int>({2, 5, 3});
    Y[3] = vector<int>({-1, 2, -3});
    X[4] = vector<int>({6, 3, 0, 7});
    Y[4] = vector<int>({-1, 6, 3, 0});
    X[5] = vector<int>({8, 3, 6, 0, 9});
    Y[5] = vector<int>({-1, 8, 3, 6, 0});
    X[6] = vector<int>({10, 7, 2, 6, 0, 11});
    Y[6] = vector<int>({-1, 10, 7, 2, 6, 0});
    X[7] = vector<int>({8, 5, 12, 3, 9, 0, 13});
    Y[7] = vector<int>({-1, 8, 5, 12, 3, 9, 0});
    int N;
    cin >> N;
    deal(0, N);
    return 0;
}
