#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    vector<int> h;
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int j;
        cin >> j;
        h.push_back(j);
    }
    
    sort(h.begin(), h.end());
    
    int res = n;
    for (int i = 0; i < n; ++i)
        if (n - i - 1 + h[i] < res) res = n - i - 1 + h[i];
    
    cout << res << endl;

    return 0;
}
