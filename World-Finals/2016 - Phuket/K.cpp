#include <iostream>
using namespace std;

const int MAXN = 101;

int N;
int X[MAXN];

bool check(int j) {
    int a = 0, b = 0;
    for (int i = j; i > 0; --i) {
        if (X[a] - b < i) return false;
        if (X[a] - b == i) {
            ++a;
            b = 0;
        } else
            b += i;
    }
    a = N - 1;
    b = 0;
    for (int i = j; i > 0; --i) {
        if (X[a] - b < i) return false;
        if (X[a] - b == i) {
            --a;
            b = 0;
        } else
            b += i;
    }
    return true;
}

int main() {
    cin >> N;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
        sum += X[i];
    }
    if (sum & 1) {
        cout << "no quotation" << endl;
        return 0;
    }
    for (int i = 100; i >= 2; --i) {
        if ((i + 1) * i > sum) continue;
        if (check(i)) {
            cout << i << endl;
            return 0;
        }
    }
    if (sum == 2)
        cout << 1 << endl;
    else 
        cout << "no quotation" << endl;
    return 0;
}
