#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - III Stage
    Problem name: FarmerCraft
    Problem link: https://szkopul.edu.pl/problemset/problem/vxIJvdKsTWZup9JYnSgRZPT3/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 5e5+5;
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;

int n;
vector<int> G[MAX_N];
ll t[MAX_N], k[MAX_N], a[MAX_N];

bool comp(int x, int y) {
    return (t[x] - k[x]) > (t[y] - k[y]);
}

void dfs(int v, int par) {
    if (G[v].size() == 1 && v != 1) {
        t[v] = a[v];
        k[v] = 0LL;
        return;
    }

    t[v] = a[v];
    vector<int> children;
    for (auto to: G[v]) {
        if (to == par) continue;
        children.push_back(to);
        dfs(to, v);
        k[v] += k[to] + 2;
    }
    sort(children.begin(), children.end(), comp);
    ll edgesUsed = 0LL;
    for (int i = 0; i < children.size(); i++) {
        int child = children[i];
        t[v] = max(t[v], t[child] + edgesUsed + 1);
        edgesUsed += k[child] + 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, -1);

    cout << max(t[1], a[1] + k[1]);

    return 0;
}
