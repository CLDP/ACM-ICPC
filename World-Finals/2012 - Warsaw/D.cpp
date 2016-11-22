#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 100100;
const int MAXM = 100010;


string fl0, fl1, fr0, fr1, fl2, fr2, fm;
long long g0, g1, g2;
int next[MAXN];

int Get_Next(const string &p) {
    int j = 1, k = -1;
    next[0] = -1;
    while (j < p.size()) 
     if (k == -1 || p[j] == p[k]) {
         next[++j] = ++k;
     } else k = next[k];
    return 0;
}

long long KMP(string &p, string &q) {   //find the position    p in q
    int lenp = p.size(), lenq = q.size();
    long long ans = 0;
    int i = 0, j = 0;
    while (i < lenp && j < lenq)
     if (i == -1 || p[i] == q[j]) {
         ++i;
         ++j;
         if (i == lenp - 1) ++ans;
     } else i = next[i];
     return ans;
}


int main() {
    int n, times = 0;
    while (cin >> n) {
        ++times;
        string p;
        cin >> p;
        g0 = g1 = 0;
        if (p.size() == 1) {
            if (p == "1")
                g1 = 1;
            else
                g0 = 1;
        }
        
        p = p + "2";
        Get_Next(p);
        if (p.size() == 2) {
            fl0 = fr0 = fl1 = fr1 = "";
        } else {
            fl0 = fr0 = "0";
            fl1 = fr1 = "1";
        }
        
        if (n >= 2) {
            int len = p.size() - 1;
            for (int i = 2; i <= n; ++i) {
                fl2 = fl1 + fl0;
                if (fl2.size() >= len) fl2 = fl2.substr(0, len - 1);
                fr2 = fr1 + fr0;
                if (fr2.size() >= len) fr2 = fr2.substr(fr2.size() - (len - 1), len - 1);
                fm = fr1 + fl0;
                if (fm.size() > 0) 
                    g2 = g0 + g1 + KMP(p, fm);
                else
                    g2 = g0 + g1;
                g0 = g1;
                g1 = g2;
                fl0 = fl1;
                fl1 = fl2;
                fr0 = fr1;
                fr1 = fr2;
            }
            cout << "Case " << times << ": " << g2 << endl;
        } else {
            if (n == 1) {
                cout << "Case " << times << ": " << g1 << endl;
            } else {
                cout << "Case " << times << ": " << g0 << endl;
            }
        }
    }
    
    return 0;
}
