#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;


const double PI = 3.14159265358979323846;

struct node {
    int x, y;
    double d;
};

bool compare(const node &a, const node &b) {
    return a.d < b.d;
}

int main() {
    int n, x0, y0, d, times = 0;
    cin >> n >> x0 >> y0 >> d;
    while (n > 0) {
        ++times;
        vector<node> all;
        for (int i = 0; i < n; ++i) {
            node p;
            cin >> p.x >> p.y;
            p.d = atan((p.y - y0 + 1e-10) / (p.x - x0 + 1e-10)) / PI * 180;
            if (p.x < x0) p.d -= 180;
            all.push_back(p);
        }
        sort(all.begin(), all.end(), compare);
        
        for (int i = 0; i < n; ++i) {
            node p = all[i];
            p.d += 360;
            all.push_back(p);
        }
        
        int ans = 1000;
        for (int i = 0; i < n; ++i) {
            int temp = 1, k = i;
            for (int j = i; j < i + n; ++j) {
                if (all[k].d + d < all[j].d + 1e-8) {
                    k = j;
                    ++temp;
                }
            }
            if (temp < ans) ans = temp;
        }
        
        cout << "Case " << times << ": " << ans << endl; 
        cin >> n >> x0 >> y0 >> d;
    }

    return 0;
}
