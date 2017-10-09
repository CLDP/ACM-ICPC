#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 10010;

int x[MAXN], y[MAXN], a[MAXN], b[MAXN], c[MAXN];
string P[MAXN];

double X[MAXN], Y[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int N, M, R;
    cin >> N >> M >> R;
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
    for (int i = 0; i < M; ++i) cin >> a[i] >> b[i] >> c[i];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (a[j] * x[i] + b[j] * y[i] + c[j] > 0) P[i] = P[i] + "1"; else P[i] = P[i] + "0";
        }
        for (int j = 0; j < i; ++j) {
            if (P[i] == P[j]) {
                cout << "no" << endl;
                return 0;
            }
        }
    }

    int k = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = i + 1; j < M; ++j) {
            if (a[i] * b[j] == a[j] * b[i]) continue;
            double XP = 1.0 * (b[i] * c[j] - b[j] * c[i]) / (a[i] * b[j] - a[j] * b[i]);
            double YP = 1.0 * (a[i] * c[j] - a[j] * c[i]) / (b[i] * a[j] - b[j] * a[i]);
            if (XP * XP + YP * YP >= R * R + 1e-8) continue;
            bool flag = true;
            for (int t = 0; t < k; ++t) {
                if (fabs(XP - X[i]) < 1e-8 && fabs(YP - Y[i]) < 1e-8) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                X[k] = XP;
                Y[k] = YP;
                ++k;
            }
        }
    }

    if (N == M + 1 + k) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }


    return 0;
}
