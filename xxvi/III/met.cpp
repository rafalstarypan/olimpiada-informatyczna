#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - III stage
	Problem name: Metro
	Problem link: https://szkopul.edu.pl/problemset/problem/hxMnCQMERV9OY1QwAdEXxQFy/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 3e6+5;
const int M = 3e4+5;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

int n, k;
set<int> G[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> k;
	for (int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		G[u].insert(v);
		G[v].insert(u);
	}
	
	vector<int> leaves;
	for (int i = 1; i <= n; i++) {
		if (G[i].size() == 1) leaves.push_back(i);
	}
	
	int R = 0;
	while (leaves.size() > k) {
		R++;
		vector<int> new_leaves;
		
		for (int v: leaves) {
			int p = *G[v].begin();
			if (G[p].size() > 1) {
				G[p].erase(v);
				if (G[p].size() == 1) new_leaves.push_back(p);
			}
		}
		
		leaves = new_leaves;
	}
	
	if (leaves.size() == 1) {
		int v = leaves[0];
		leaves.push_back(*G[v].begin());
	}
	
	cout << R << ' ' << leaves.size() << '\n';
	for (int i: leaves) cout << i << ' ';
	cout << '\n';
	
    return 0;
}
