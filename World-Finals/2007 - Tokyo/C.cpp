#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;
const double PI = acos(-1.0);


pair<double, double> mergeA(pair<double, double> A, pair<double, double> B) {
    pair<double, double> ans;
    ans.first = max(A.first, B.first);
    ans.second = min(A.second, B.second);
    if (ans.first <= ans.second) return ans; else return make_pair(-1, -1);
}

int accept(int &times) {
    cout << "Case " << ++times << ": Acceptable as proposed" << endl << endl;
    return 0;
}

int main() {
    int N, D, times = 0;
    while (cin >> N >> D) {
        if (N == 0) break;
        vector<pair<double, double> > X(N + 1);
        X[0] = make_pair(0, 0);
        for (int i = 1; i <= N; ++i) cin >> X[i].first >> X[i].second;
        if (D == 0) {
            accept(times);
            continue;
        }
        
        bool Bclock = false, Bcounter = false;
        vector<pair<double, double> > clock, counter;
        for (int i = 0; i < N; ++i) {
            double DD = atan2(X[i + 1].second - X[i].second, X[i + 1].first - X[i].first) * 180 / PI;
            
            if (DD == -90) {
                counter.push_back(make_pair(0, 180));
                Bclock = true;
            } else
            if (DD == 90) {
                clock.push_back(make_pair(0, 180));
                Bcounter = true;
            } else
            if (-90 < DD && DD < 90) {
                counter.push_back(make_pair(0, 90 - DD));
                clock.push_back(make_pair(0, DD + 90));
            } else
            if (DD > 90) {
                clock.push_back(make_pair(DD - 90, 180));
                counter.push_back(make_pair(270 - DD, 180));
            } else {
                counter.push_back(make_pair(-90 - DD, 180));
                clock.push_back(make_pair(270 + DD, 180));
            }
        }
        
        pair<double, double> ans1, ans2;
        ans1 = ans2 = make_pair(0, 180);
        for (int i = 0; i < clock.size(); ++i) ans1 = mergeA(ans1, clock[i]);
        for (int i = 0; i < counter.size(); ++i) ans2 = mergeA(ans2, counter[i]);
        if (fabs(ans1.first) < 1e-5 || fabs(ans2.first) < 1e-5) {
            accept(times);
            continue;
        }
        
        if (Bclock && ans1.first != -1) {
            if (ans1.second == 180) ans1.first = 180; else ans1 = make_pair(-1, -1);
        }
        if (Bcounter && ans2.first != -1) {
            if (ans2.second == 180) ans2.first = 180; else ans2 = make_pair(-1, -1);
        }
        
        if (ans1.first == -1) {
            if (ans2.first == -1) {
                cout << "Case " << ++times << ": Unacceptable" << endl << endl;
            } else {
                cout << "Case " << ++times << ": Acceptable after counterclockwise rotation of ";
                printf("%.2lf degrees\n\n", ans2.first);
            }
        } else {
            if (ans2.first == -1) {
                cout << "Case " << ++times << ": Acceptable after clockwise rotation of ";
                printf("%.2lf degrees\n\n", ans1.first);
            } else {
                if (ans1.first <= ans2.first) {
                    cout << "Case " << ++times << ": Acceptable after clockwise rotation of ";
                    printf("%.2lf degrees\n\n", ans1.first);
                } else {
                    cout << "Case " << ++times << ": Acceptable after counterclockwise rotation of ";
                    printf("%.2lf degrees\n\n", ans2.first);
                }
            }
        }
    }
    return 0;
}
