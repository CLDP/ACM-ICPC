#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
const double EPS = 1e-8;

int N;
bool z[MAXN];
int l[MAXN], t[MAXN];
vector<int> T[MAXN];

double calT(double v) {
    double time = 0, curr = 0;
    for (int k = 0; k < N; ++k) {
        int i = t[k];
        if (z[i]) {
            double currM = curr / 60;
            currM -= ((int)(currM / 60)) * 60;
            int currMI = currM;
            if (fabs(currM - currMI) > EPS) ++currMI;
            
            for (int j = 0; j < T[i].size(); ++j) {
                if (T[i][j] < currMI) continue;
                time += (T[i][j] - currM) * 60;
                curr += (T[i][j] - currM) * 60;
                time += l[i] * 60;
                curr += l[i] * 60;
                break;
            }
        } else {
            time += l[i] / v * 3600;
            curr += l[i] / v * 3600;
        }
    }
    return time;
}


string getS(int T) {
    string SS;
    if (T < 10) {
        SS = "0";
        SS = SS + (char)(T + '0');
    } else {
        SS = (char)(T / 10 + '0');
        SS = SS + (char)(T % 10 + '0');
    }
    return SS;
}

int main() {
    int times = 0;
    while (++times) {
        cin >> N;
        if (N == 0) break;
        map<string, string> C;
        map<string, int> IN, CT;
        for (int i = 0; i < N; ++i) {
            string P, Q, R;
            cin >> Q >> R >> P;
            C[Q] = R;
            CT[Q] = i;
            IN[Q] += 0;
            IN[R] += 1;
            if (P == "road") {
                z[i] = false;
                cin >> l[i];
            } else {
                z[i] = true;
                int M;
                cin >> l[i] >> M;
                T[i] = vector<int>(M, 0);
                for (int j = 0; j < M; ++j) cin >> T[i][j];
                sort(T[i].begin(), T[i].end());
                T[i].push_back(T[i][0] + 60);
            }
        }
        string ST;
        for (map<string, int>::iterator i = IN.begin(); i != IN.end(); ++i) {
            if (i->second == 0) {
                ST = i->first;
                break;
            }
        }
        for (int i = 0; i < N; ++i) {
            t[i] = CT[ST];
            ST = C[ST];
        }
        
        double minT = calT(80);
        double L = 0, R = 80;
        while (L + EPS < R) {
            double mid = (L + R) / 2;
            double tempT = calT(mid);
            if (fabs(tempT - minT) < EPS) R = mid; else L = mid;
        }
        int timeT = ceil(minT);
        string ansT;
        ansT = getS(timeT / 3600) + ":" + getS(timeT / 60 % 60) + ":" + getS(timeT % 60);
        cout << "Test Case " << times << ": " << ansT << " ";
        printf("%.2lf\n\n", R);
    }
    return 0;
}
