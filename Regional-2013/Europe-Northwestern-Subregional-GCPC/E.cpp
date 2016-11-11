#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 10000000;
const double PI = 3.14159265358979323846;



int main() {
    double V;
    int n;
    cin >> V >> n;
    int ansT = 0;
    double ansM = 1e100;
    for (int j = 0; j < n; ++j) {
        double a, b, c;
        cin >> a >> b >> c;
        double ans = 0;
        for (int i = 0; i < INF; ++i) {
            double t = i * c / INF;
            double pp = a * exp(- t * t) + b * sqrt(t);
            t = (i + 1) * c / INF;
            double qq = a * exp(- t * t) + b * sqrt(t);;
            double rr = (pp + qq) / 2;
            ans += rr * rr;
        }
        ans *= PI * c / INF;
        if (fabs(ans - V) < ansM) {
            ansT = j;
            ansM = fabs(ans - V);
        }
    }
    
    cout << ansT << endl;
    
    return 0;
}
