#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

long long x[110];

long long getN(string P) {
    istringstream PIN(P);
    long long ans;
    PIN >> ans;
    return ans;
}

int deal(string P) {
    istringstream PIN(P);
    long long A, B;
    char trash;
    
    if (P[1] == 'n') {
        if (P[0] == '+') A = 1; else A = -1;
        if (P.size() == 2) 
            B = 1;
        else
            PIN >> trash >> trash >> trash >> B;
    } else {
        string Q = P + "#";
        istringstream QIN(Q);
        QIN >> trash >> A >> trash;
        if (trash == '#') 
            B = 0;
        else
        if (P[P.size() - 1] == 'n')
            B = 1;
        else
            QIN >> trash >> B;
        if (P[0] == '-') A = -A;
    }
    x[B] += A;
    return 0;
}

long long GCD(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    } 
    return a;
}


long long cal(long long a, long long MOD) {
    long long t = 1, ans = 0;
    for (int i = 0; i <= 100; ++i) {
        ans = ((ans + t * x[i]) % MOD + MOD) % MOD;
        t = (t * a) % MOD;
    }
    return ans;
}

int main() {
    int times = 0;
    string P;
    while (cin >> P) {
        if (P == ".") break;
        memset(x, 0, sizeof(x));
        long long de = 0;
        for (int i = 1; i < P.size(); ++i) {
            int j = i;
            ++j;
            while (P[j] != '+' && P[j] != '-' && P[j] != ')') ++j;
            if (i == 1 && P[1] != '-') deal("+" + P.substr(i, j - i)); else deal(P.substr(i, j - i));
            if (P[j] == ')') {
                i = j + 2;
                j = P.size();
                de = getN(P.substr(i, j - i));
                break;
            } else {
                i = j - 1;
                continue;
            }
        }
        
        long long gcd = de;
        for (int i = 0; i <= 100; ++i)
         if (x[i] != 0) gcd = GCD(gcd, x[i]);
        for (int i = 0; i <= 100; ++i) x[i] /= gcd;
        de /= gcd;
        
        long long temp = de;
        for (int i = 2; i <= 110; ++i) {
            if (temp % i == 0) {
                while (temp % i == 0) temp /= i;
            }
        }
        if (temp > 1) {
            cout << "Case " << ++times << ": Not always an integer" << endl;
            continue;
        }
        bool flag = true;
        for (int i = 0; i < 1000; ++i) {
            long long ans = cal(i, de);
            if (ans != 0) {
                cout << "Case " << ++times << ": Not always an integer" << endl;
                flag = false;
                break;
            }
        }
        
        if (flag) {
            cout << "Case " << ++times << ": Always an integer" << endl;
        }
    }
    return 0;
}
