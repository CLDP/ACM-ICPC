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

long long f[55];

int main() {
    int n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> v(n);
        vector<int> s;
        
        for (int i = 0; i < n; ++i) cin >> v[i];
        
        long long res = 0;
        s.push_back(v[0]);
        for (int i = 1; i < n; ++i) {
            sort(s.begin(), s.end());
            f[0] = 1;
            s.push_back(v[i]);
            for (int j = 1; j < i; ++j) {
                f[j] = 1;
                int ind = 0;
                while (s[j] > s[ind]) f[j] += f[ind++];
            }
            if (s[i] >= s[i - 1]) continue;
            res++;
            for (int j = 0; j < i; ++j)
                if (s[i] > s[j])
                    res += f[j];
                else
                    break;
        }
        
        cout << res << endl;
    }

    return 0;
}
