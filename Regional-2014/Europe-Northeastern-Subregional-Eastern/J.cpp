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

struct node {
    int v, ind;
};

node tn;
vector<node> v1, v2;
int t1, t2;

bool compare(node n1, node n2) {
    return n1.v < n2.v;
}

int main() {
    int n;
    
    cin >> n;
    t1 = 0;
    t2 = 0;
    for (tn.ind = 1; tn.ind <= n; ++tn.ind) {
        cin >> tn.v;
        t1 += tn.v;
        v1.push_back(tn);
    }
    for (tn.ind = 1; tn.ind <= n; ++tn.ind) {
        cin >> tn.v;
        t2 += tn.v;
        v2.push_back(tn);
    }
    
    sort(v1.begin(), v1.end(), compare);
    sort(v2.begin(), v2.end(), compare);
    
    if (t1 < t2) {
        for (int i = 0; i < n; ++i)
            cout << v1[n-1-i].ind << " " << v2[i].ind << endl;
    } else {
        for (int i = 0; i < n; ++i)
            cout << v1[i].ind << " " << v2[n-1-i].ind << endl;
    }

    return 0;
}
