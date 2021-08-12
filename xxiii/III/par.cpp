#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIII OI - III Stage
    Problem name: Parada
    Problem link: https://szkopul.edu.pl/problemset/problem/1QaUWE_ePAmitZjgAszOVD1U/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 3e5+5;
const ll MOD = (ll)(1e9+7);
const ll INF = (ll) (1e18);
const int inf = 1e9;

int n;
int ans = -1;
vector<int> G[MAX_N];

int dfs(int node, int parent) {
	int s = (int)G[node].size();
    int maxi = 0, secondMaxi = 0;

    for (auto adj: G[node]) {
        if (adj == parent) continue;
        int cur = dfs(adj, node);
        if (cur > maxi) {
            secondMaxi = maxi;
            maxi = cur;
        } else if (cur > secondMaxi) {
            secondMaxi = cur;
        }
    }
    ans = max(ans, maxi + secondMaxi + s - 2 + (secondMaxi == 0));
    return maxi + s - 2 + (maxi == 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    if (n <= 2) {
        cout << 0;
        return 0;
    }

    dfs(1, -1);
    cout << ans;

    return 0;
}
