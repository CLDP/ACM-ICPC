#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-10;

struct node {
    int a, b, g, ID;
    
    bool operator < (const node &B) const {
        return 1.0 * a / b > 1.0 * B.a / B.b;
    }
};

const int MAXN = 100010;

double Y[MAXN];

int main() {
    freopen("burrito.in", "r", stdin);
    freopen("burrito.out", "w", stdout);
    int N, A, B;
    scanf("%d%d%d", &N, &A, &B); 
    
    double AA = 0, BB = 0; 
    vector<node> X;
    for (int i = 0; i < N; ++i) {
        node P;
        scanf("%d%d%d", &P.g, &P.a, &P.b);
        if (P.b == 0) {
            Y[i] = P.g;
            AA += P.g * P.a;
            continue;
        }
        if (P.a == 0) {
            continue;
        }
        P.ID = i;
        X.push_back(P);
    }
    sort(X.begin(), X.end());
    
    for (int i = 0; i < X.size(); ++i) {
        if (BB + X[i].g * X[i].b <= B + EPS) {
            BB += X[i].g * X[i].b;
            AA += X[i].g * X[i].a;
            Y[X[i].ID] = X[i].g;
        } else {
            Y[X[i].ID] = (B - BB) / X[i].b;
            AA += (B - BB) / X[i].b * X[i].a;
            BB = B;
            break;
        }
    }
    
    if (AA <= A - EPS) {
        cout << "-1 -1" << endl;
        return 0;
    }
    printf("%.10lf %.10lf\n", AA, BB);
    for (int i = 0; i < N; ++i) printf("%.10lf ", Y[i]);
    printf("\n");
    return 0;
}
