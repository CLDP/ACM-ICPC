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

vector<pair<int, int> > st[30];

int main() {
    vector<char> v;
    
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    for (int i = 1; i <= n; i++) {
        getline(cin, s);
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == '{')
                v.push_back(s[j]);
            else 
            if (s[j] == '}') {
                while (v.back() != '{') {
                    st[v.back() - 'a'].pop_back();
                    v.pop_back();
                }
                v.pop_back();
            } else 
            if (s[j] != ' ') {
                int ind = s[j] - 'a';
                if (!st[ind].empty()) {
                    cout << i << ":" << j + 1 << ": warning: shadowed declaration of " << s[j];
                    cout << ", the shadowed position is " << st[ind].back().first << ":" << st[ind].back().second << endl;
                }
                st[ind].push_back(make_pair(i, j + 1));
                v.push_back(s[j]);
            }
        }
    }

    return 0;
}
