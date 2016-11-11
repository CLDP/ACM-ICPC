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


int main() {
    int n, res = 0, cur = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int next = 0;
        if (s <= "Aurora")
            next = 0;
        else if (s <= "Bolt")
            next = 1;
        else if (s <= "Kuzko")
            next = 2;
        else if (s <= "Mulan")
            next = 1;
        else if (s <= "Robin")
            next = 0;
        else if (s <= "Stitch")
            next = 1;
        else 
            next = 2;
        res += abs(next - cur);
        cur = next;
    }
    
    cout << res << endl;

    return 0;
}
