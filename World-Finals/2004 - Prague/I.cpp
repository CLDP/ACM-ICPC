#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;


double calA(double a, double c, double x) {
    return x / 2 * sqrt(a * x * x + c) + c / (2 * sqrt(a)) * log(x * sqrt(a) + sqrt(a * x * x + c));
}

double cal(int N, int M, double C, double D) {
    double B;
    if (N == M) {
        B = D / 2;
    } else {
        double a = (N - M) * 3;
        double b = 2 * D * (M * 3 - 2 - C);
        double c = - D * D * (M * 3 - 2 - C);
        B = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        if (B < 0 || B > D) B = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    }
    double A = (M * 3 - 2 - C) / (B * B);
    return calA(4 * A * A, 1, B) + calA(4 * A * A, 1, D - B);
}

int main() {
    int N, M, times = 0;
    double D;
    bool first = true;
    while (cin >> N >> M >> D) {
        if (N == 0 && M == 0) break;
        if (!first) cout << endl;
        first = false;
        vector<string> X(N), Y(M);
        for (int i = 0; i < N; ++i) cin >> X[i];
        for (int i = 0; i < M; ++i) cin >> Y[i];
        
        int ans = -1;
        for (int i = 1; i < min(N, M); ++i) {
            int B = (X[i - 1] == "B") + (Y[i - 1] == "B");
            int C = (Y[i - 1] == "C") + (X[i - 1] == "C");
            if (B == 0 || C == 0) {
                ans = (i - 1) * 6 + 2;
                break;
            }
            
            B = (X[i - 1] == "B") + (Y[i - 1] == "B");
            C = (X[i] == "C") + (Y[i] == "C");
            if (B == 0 || C == 0) {
                ans = (i - 1) * 6 + 3;
                break;
            }
        }
        
        if (ans == -1) {
            cout << "Case " << ++times << ": impossible" << endl;
            continue;
        }
        
        printf("Case %d: %.3lf\n", ++times, cal(N, M, 0.5 * ans + 1, D));
    }
    return 0;
}
