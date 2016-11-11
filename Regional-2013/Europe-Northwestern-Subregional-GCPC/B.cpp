#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;
const double PI = 3.14159265358979323846;


const int M[14] = {0, 0, 31, 31 + 28, 59 + 31, 90 + 30, 120 + 31, 151 + 30, 181 + 31, 212 + 31, 243 + 30, 273 + 31, 304 + 30, 334 + 31};


struct node {
    int s, e;
};

int times, n, C;

int getN(int a, int b, int c, int d, int e) {
    int ans = e;
    ans += d * 60;
    ans += c * 24 * 60;
    ans += M[b] * 24 * 60;
    if (a == 6 && b > 2) ans += 24 * 60;
    
    if (a == 4)
        ans += 365 *24 * 60;
    else if (a == 5)
        ans += 365 *24 * 60 * 2;
    else if (a == 6)
        ans += 365 *24 * 60 * 3;
    return ans;
}

bool compare(const node &a, const node &b) {
    if (a.s < b.s) return true;
    if (a.s > b.s) return false;
    return a.e < b.e;
}


int main() {
    cin >> times;
    while (times > 0) {
        --times;
        cin >> n >> C;
        string p, d1, t1, d2, t2;
        vector<node> res;
        res.clear();
        for (int i = 0; i < n; ++i) {
            cin >> p >> d1 >> t1 >> d2 >> t2;
            node tt;
            tt.s = getN(d1[3] - '0', (d1[5] - '0') * 10 + d1[6] - '0', (d1[8] - '0') * 10 + d1[9] - '0', (t1[0] - '0') * 10 + t1[1] - '0', (t1[3] - '0') * 10 + t1[4] - '0');
            tt.e = getN(d2[3] - '0', (d2[5] - '0') * 10 + d2[6] - '0', (d2[8] - '0') * 10 + d2[9] - '0', (t2[0] - '0') * 10 + t2[1] - '0', (t2[3] - '0') * 10 + t2[4] - '0');
            res.push_back(tt);
        }
        sort(res.begin(), res.end(), compare);
        
        vector<int> endd;
        for (int i = 0; i < n; ++i) {
            int m = endd.size();
            bool flag = false;
            for (int j = 0; j < m; ++j) {
                if (endd[j] <= res[i].s) {
                    endd[j] = res[i].e + C;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                endd.push_back(res[i].e + C);
            }
        }
        
        cout << endd.size() << endl;
    }
    
    
    return 0;
}
