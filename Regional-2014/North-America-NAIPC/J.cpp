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
    int k;
    string s;
    
    cin >> k;
    s = "a";
    
    if (k <= 25) {
        s += ('a' + k);
        cout << s << endl;
    } else 
    if (k <= 50) {
        s += ('a' + (k + 1) / 2);
        s += ('a' + k % 2);
        cout << s << endl;
    } else {
        int i = ((k - 1) % 25) + 26;
        s += ('a' + (i + 1) / 2);
        s += 'a';
        char c = 'a';
        k = k - (i + 1) / 2 * 2;
        while (k > 25) {
            if (c == 'a')
                c = 'z';
            else
                c = 'a';
            s += c;
            k -= 25;
        }
        if (c == 'a')
            s += (c + k);
        else
            s += (c - k);
        cout << s << endl;
    }
    
    return 0;
}
