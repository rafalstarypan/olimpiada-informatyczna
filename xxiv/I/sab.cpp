#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - I Stage
    Problem name: Sabotaz
    Problem link: https://szkopul.edu.pl/problemset/problem/CUjJDGGSEZmO7HvdZU4FKrL6/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<int, ll> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 5e5+5;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;

int n, k;
vector<int> G[MAX_N];
int sizes[MAX_N], par[MAX_N];
double dp[MAX_N];

void dfs1(int v, int parent) {
    sizes[v] = 1;
    par[v] = parent;
    for (auto adj: G[v]) {
        if (adj == parent) continue;
        dfs1(adj, v);
        sizes[v] += sizes[adj];
    }
}

void dfs2(int v, int parent) {
    if (sizes[v] == 1 && v != 1) {
        dp[v] = 1;
        return;
    }

    for (auto adj: G[v]) {
        if (adj == parent) continue;
        dfs2(adj, v);
        double val1 = dp[adj];
        double val2 = (double)sizes[adj] / (double)(sizes[v] - 1);
        double tmp = min(val1, val2);
        dp[v] = max(dp[v], tmp);
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    if (n == 1 || n == k) {
        cout << "0.000000";
        return 0;
    }

    for (int i=2; i<=n; i++) {
        int p; cin >> p;
        G[p].push_back(i);
        G[i].push_back(p);
    }

    dfs1(1, -1);
    dfs2(1, -1);

    double ans = dp[1];
    for (int i=2; i<=n; i++) {
        if (sizes[i] > k) {
            ans = max(ans, dp[i]);
        }
    }

    cout << fixed << setprecision(10) << ans;

    return 0;
}
