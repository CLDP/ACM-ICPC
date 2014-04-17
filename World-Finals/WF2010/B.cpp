#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int a[200];
    int b[200];
    int code[55];
    
    for (int i = 0; i < 34; ++i) code[i] = -1;
    code[1] = 0;
    code[17] = 1;
    code[9] = 2;
    code[24] = 3;
    code[5] = 4;
    code[20] = 5;
    code[12] = 6;
    code[3] = 7;
    code[18] = 8;
    code[16] = 9;
    code[4] = 10;
    
    int M, times = 0;
    while (cin >> M) {
        if (M == 0) break;
        int N = (M - 23) / 6;
        double nmin = 300;
        for (int i = 0; i < M; ++i) {
            cin >> a[i];
            if (a[i] < nmin) nmin = a[i];
        }
        if ((M <= 23) || ((M - 23) % 6 > 0)) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        double nmax = 0, wmax = 0, wmin = 300;
        for (int i = 0; i < M; ++i) {
            if ((a[i] >= nmin) && (a[i] <= nmin * 21 / 19)) {
                b[i] = 0;
                if (a[i] > nmax) nmax = a[i];
            } else {
                if (a[i] < wmin) wmin = a[i];
                if (a[i] > wmax) wmax = a[i];
                b[i] = 1;
            }
        }
        
        if (wmax > wmin * 21 / 19) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        double l1 = nmax * 20 / 21;
        double r1 = nmin * 20 / 19;
        double l2 = wmax * 20 / 21;
        double r2 = wmin * 20 / 19;
        if ((l2 > r1 * 2) || (r2 < l1 * 2)) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        if (b[1] == b[M - 2]) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        if (b[M - 2] == 0) {
            int i = 0, j = M - 1;
            while (i < j) {
                int k = b[i];
                b[i] = b[j];
                b[j] = k;
                ++i;
                --j;
            }
        }
        
        int s1 = 0, s2 = 0;
        for (int i = 0; i < 5; ++i) {
            s1 = s1 * 2 + b[i];
            s2 = s2 * 2 + b[M - 5 + i];
        }
        if ((s1 != 6) || (s2 != 6)) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        bool inter = true;
        for (int i = 5; i < M; i += 6) {
            if (b[i] != 0) inter = false;
        }
        if (!inter) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        int c = 0, k = 0;
        bool badcode = false;
        vector<int> cc;
        for (int i = 1; i <= N; i++) {
            int num = 0;
            for (int j = 0; j < 5; ++j) num = num * 2 + b[i * 6 + j];
            if (code[num] == -1) badcode = true;
            c = (c + (((N - i) % 10 + 1) * code[num])) % 11;
            k = (k + (((N - i + 1) % 9 + 1) * code[num])) % 11;
            cc.push_back(code[num]);
        }
        k = (k + c) % 11;
        int cnum = 0, knum = 0;
        for (int i = 0; i < 5; ++i) {
            cnum = cnum * 2 + b[M - 17 + i];
            knum = knum * 2 + b[M - 11 + i];
        }
        if ((code[cnum] == -1) || (code[knum] == -1)) badcode = true;
        
        if (badcode) {
            cout << "Case " << ++times << ": bad code" << endl;
            continue;
        }
        
        if (c != code[cnum]) {
            cout << "Case " << ++times << ": bad C" << endl;
            continue;
        }
        
        if (k != code[knum]) {
            cout << "Case " << ++times << ": bad K" << endl;
            continue;
        }
        
        cout << "Case " << ++times << ": ";
        for (int i = 0; i < cc.size(); ++i) {
            if (cc[i] < 10)
                cout << cc[i];
            else
                cout << "-";
        }
        cout << endl;
    }
    
    return 0;
}
