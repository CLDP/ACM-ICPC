const int MAXN = 200100;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];

// n must be total number of vertices
// If too slow, try to do something obvious before call this function
// This algorithm is not sensitive to the depth of the graph,
// but to the number of augmenting path of course
int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> fi(n + 1, 0);
     vector<bool> z(n + 1, 0);
    
    int i = 0, now, ans = 0;
    
    i = s;
    now = INF;
    
    while (true) {
        z[i] = true;
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
             if (p->second > 0 && !z[p->first]) {
                flag = true;
                if (p->second < now) now = p->second;
                fa[p->first] = i;
                fi[p->first] = p - x[i].begin();
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
                        p->second -=now;
                        x[tmp].push_back(make_pair(i, now));
                    }
                    now = INF;
                    z = vector<bool> (n + 1, false);
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        if (!flag && i == s) break;
        
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}
