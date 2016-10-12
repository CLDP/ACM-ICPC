int N, M, NN;
bool z[MAXN];
int list[MAXN];
vector<int> x[MAXN], y[MAXN];

void back(int a) {
    z[a] = true; cout << a << " ";
    for (int i = 0; i < y[a].size(); ++i) 
     if (!z[y[a][i]]) back(y[a][i]);
}

void dfs(int a) {
    z[a] = true;
    for (int i = 0; i < x[a].size(); ++i) 
     if (!z[x[a][i]]) dfs(x[a][i]);
    list[NN--] = a;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        x[a].push_back(b);
        y[b].push_back(a);
    }
    memset(z, 0, sizeof(z));
    NN = N;
    for (int i = 1; i <= N; ++i) if (!z[i]) dfs(i);
    memset(z, 0, sizeof(z));
    
    for (int i = 1; i <= N; ++i) 
     if (!z[list[i]]) {
         back(list[i]);
         cout << endl;
     }
    return 0;
}
