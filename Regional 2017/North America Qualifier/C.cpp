#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 5000010;

int f[MAXN];
int x[110];

bool check(int a, int N) {
    int ans = f[a];
    int k = N - 1;
    int temp = 0;
    while (a > 0) {
        temp += a / x[k];
        a = a % x[k];
        --k;
    }
    return ans == temp;
}


int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;

    for (int i = 0; i < MAXN; ++i) f[i] = MAXN + MAXN;
    f[0] = 0;

    for (int i = 0; i < N; ++i) {
        cin >> x[i];
        for (int j = x[i]; j < MAXN; ++j) f[j] = min(f[j], f[j - x[i]] + 1);
    }

    sort(x, x + N);

    for (int i = 1; i < MAXN; ++i) {
        if (!check(i, N)) {
            cout << "non-canonical" << endl;
            return 0;
        }
    }

    cout << "canonical" << endl;
    return 0;
}
