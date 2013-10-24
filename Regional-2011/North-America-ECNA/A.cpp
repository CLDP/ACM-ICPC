#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

int n;
string p, q;
int x[MAXN];


long long cal(int lenA) {
    long long ans = 0, total = 0;
    vector<pair<int, int> > A, B, C;
    for (int i = 0; i < n; ++i) {
        if (p[i] == '1' && q[i] != '0') A.push_back(make_pair(-x[i], i));
        if (p[i] == '1' && q[i] == '0') B.push_back(make_pair(-x[i], i));
        if (p[i] == '0' && q[i] == '1') C.push_back(make_pair(-x[i], i));
        if (p[i] == '1') total += x[i];
    }
    
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    int a = 0, b = 0, lenB = B.size();
    while (a < lenA || b < lenB) {
        if (a == lenA) {
            total += B[b].first;
            ans += total;
            ++b;
        } else
        if (b == lenB) {
            total += A[a].first;
            C.push_back(A[a]);
            ans += total;
            ++a;
        } else {
            if (A[a].first < B[b].first) {
                total += A[a].first;
                C.push_back(A[a]);
                ans += total;
                ++a;
            } else {
                total += B[b].first;
                ans += total;
                ++b;
            }
        }
    }
    
    sort(C.begin(), C.end());
    for (int i = C.size() - 1; i >= 0; --i) {
        total -= C[i].first;
        ans += total;
    }
    
    return ans;
}

int main() {
    int times = 0;
    while (cin >> n) {
        if (n == 0) break;
        cin >> p >> q;
        for (int i = 0; i < n; ++i) cin >> x[i];
        int diff = 0, total = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] == '1' && q[i] == '0') ++diff;
            if (p[i] == '1') ++total;
        }
        
        long long ans = 10000000000000000, temp;
        for (int i = 0; i <= total - diff; ++i) {
            temp = cal(i);
            if (temp < ans) ans = temp;
        }
        
        ++times;
        cout << "Case " << times << ": " << ans << endl;
    }
    
    return 0;
}
