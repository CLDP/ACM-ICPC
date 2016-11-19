#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

const int MAXN = 4010;
const int INF = 1000000000;

int f[MAXN];
pair<int, string> P[MAXN];

bool inside(string &P, string &Q) {
    int L = P.size(), R = Q.size();
    int i = 0, j = 0;
    while (i < L && j < R) {
        if (P[i] == Q[j]) {
            ++i;
            ++j;
            continue;
        }
        ++j;
        continue;
    }
    return i == L;
}

int main() {
    int N;
    cin >> N;
    string Q;
    cin >> Q;
    for (int i = 0; i < N; ++i) {
        cin >> P[i].second;
        P[i].first = P[i].second.size();
    }
    sort(P, P + N);

    int a = -1, b = N, c = N, d = -1;
    string A, B, C;
    B = C = Q;
    for (int i = N - 1; i >= 0; --i) {
        if (A == "") {
            bool IB = inside(P[i].second, B);
            bool IC = inside(P[i].second, C);
            if (!IB && !IC) {
                cout << "impossible" << endl;
                return 0;
            }
            if (IB && IC) {
                A = P[i].second;
                a = d = i;
                continue;
            }
            if (IB) {
                B = P[i].second; 
                f[i] = b;
                b = i;
            } else {
                C = P[i].second;
                f[i] = c;
                c = i;
            }
        } else {
            bool IA = inside(P[i].second, A);
            if (IA) {
                A = P[i].second;
                f[i] = a;
                a = i;
                continue;
            }
            bool IB = inside(P[i].second, B);
            bool IC = inside(P[i].second, C);
            if (IB || IC) {
                if (IB) {
                    f[i] = b; 
                    f[d] = c;
                } else {
                    f[i] = c;
                    f[d] = b;
                }
                B = P[i].second; b = i;
                C = A;           c = a;
                A = "";          a = d = -1;
            } else {
                cout << "impossible" << endl;
                return 0;
            }
        }
    }

    vector<string> ans1, ans2;
    while (b != N) {
        ans2.push_back(P[b].second);
        b = f[b];
    }
    if (a != -1) {
        f[d] = c;
        while (a != N) {
            ans1.push_back(P[a].second);
            a = f[a];
        }
    } else {
        while (c != N) {
            ans1.push_back(P[c].second);
            c = f[c];
        }
    }
    cout << ans1.size() << " " << ans2.size() << endl;
    for (int i = 0; i < ans1.size(); ++i) cout << ans1[i] << endl;
    for (int i = 0; i < ans2.size(); ++i) cout << ans2[i] << endl;

    return 0;
}
