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

struct mate {
    int money, adv;
};

vector<mate> ms;
mate tm;
int bid, fid, badv;

int main() {
    bid = -1;
    fid = -1;
    badv = -1;
    
    int adv1, adv2, m;
    cin >> m >> adv1 >> adv2;
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tm.money >> tm.adv;
        ms.push_back(tm);
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num, rent, aadv;
        cin >> num >> rent >> aadv;
        if (num == 1) {
            if ((rent <= m) && (adv1 + aadv > badv)) {
                badv = adv1 + aadv;
                bid = i + 1;
                fid = -1;
            }
        } else {
            if ((rent <= m) && (adv2 + aadv > badv)) {
                badv = adv2 + aadv;
                bid = i + 1;
                fid = -1;
            }
            if (m * 2 >= rent) {
                for (int j = 0; j < ms.size(); ++j) {
                    if (ms[j].money * 2 >= rent) {
                        if (aadv + ms[j].adv > badv) {
                            badv = aadv + ms[j].adv;
                            bid = i + 1;
                            fid = j + 1;
                        }
                    }
                }
            }
        }
    }
    
    if (bid == -1)
        cout << "Forget about apartments. Live in the dormitory." << endl;
    else if (fid == -1)
        cout << "You should rent the apartment #" << bid << " alone." << endl;
    else
        cout << "You should rent the apartment #" << bid << " with the friend #" << fid << "." << endl;

    return 0;
}
