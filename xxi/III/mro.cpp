#include<bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - III Stage
    Problem name: Mrowisko
    Problem link: https://szkopul.edu.pl/problemset/problem/J5f8YHtUsaMdtOdfx0QoHKe0/site/?key=statement
*/

typedef long long ll;

const int MAX_N = 1e6+5;
const ll INF = (ll)(1e9+5);

int n, g;
ll k;
vector<int> G[MAX_N];
ll lost[MAX_N];

void dfs(int v, int p) {
	if (p != -1) {
		ll tmp = G[v].size() - 1;
		lost[v] = lost[p];
		if (tmp != 0) {
			lost[v] *= tmp;
			if (lost[v] > INF) lost[v] = INF;
		}
	}
	for (int to: G[v]) {
		if (to == p) continue;
		dfs(to, v);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> g >> k;
	vector<ll> groups(g);
	
	for (int i = 0; i < g; i++) {
		cin >> groups[i];
	}
	
	sort(groups.begin(), groups.end());
	
	int rootA, rootB;
	cin >> rootA >> rootB;
	G[rootA].push_back(n + 1);
	G[rootB].push_back(n + 1);
	G[n+1].push_back(rootA);
	G[n+1].push_back(rootB);
	
	for (int i = 0; i < n-2; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	if (G[rootA].size() == 1) {
		rootA = rootB;
	}
	
	lost[n+1] = 1LL;
	dfs(n+1, -1);
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++) {
		if (G[i].size() != 1) continue;
		ll L = lost[i] * k;
		ll R = lost[i] * (k+1) - 1;
		ll cnt = upper_bound(groups.begin(), groups.end(), R) - lower_bound(groups.begin(), groups.end(), L);
		ans += cnt * k;
	}
	
	cout << ans << '\n';
	
	return 0;
}
