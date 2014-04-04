#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;


long long abs(const long long &A) {
    return A > 0 ? A : -A;
}

long long gcd(long long a, long long b) {
    a = abs(a), b = abs(b);
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}


int main() {
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N + M == 0) break;
        vector<pair<long long, long long> > XX(N), X;
        for (int i = 0; i < N; ++i) cin >> XX[i].first >> XX[i].second;
        for (int i = 0; i < N; ++i) {
            int L = (i + 1) % N, R = (i + N - 1) % N;
            if ((XX[R].first - XX[i].first) * (XX[L].second - XX[i].second) !=
                (XX[L].first - XX[i].first) * (XX[R].second - XX[i].second)) X.push_back(XX[i]);
        }
        N = X.size();
        vector<pair<long long, long long> > Y(N);
        
        for (int i = 1; i < N; ++i) {
            Y[i].first = X[i].first - X[i - 1].first;
            Y[i].second = X[i].second - X[i - 1].second;
        }
        Y[0].first = X[0].first - X[N - 1].first;
        Y[0].second = X[0].second - X[N - 1].second;
        
        long long GCD = 0;
        for (int i = 0; i < N; ++i) {
            GCD = gcd(GCD, Y[i].first);
            GCD = gcd(GCD, Y[i].second);
        }
        
        long long edge = 0;
        for (int i = 0; i < N; ++i) {
            Y[i].first /= GCD;
            Y[i].second /= GCD;
            edge += gcd(Y[i].first, Y[i].second);
        }
        
        long long area = 0;
        long long A = Y[0].first, B = Y[0].second;
        for (int i = 1; i < N - 1; ++i) {
            long long C = A + Y[i].first, D = B + Y[i].second;
            area += A * D - B * C;
            A = C, B = D;
        }
        
        area = abs(area);
        
        unsigned long long areaF = 1ULL * M * (M + 1) / 2 * (2 * M + 1) / 3 * area / 2;
        unsigned long long edgeF = 1ULL * M * (M + 1) / 2 * edge / 2;
        unsigned long long ans = areaF + M - edgeF;
        
        cout << "Case " << ++times << ": " << ans << endl;
    }
    return 0;
}
