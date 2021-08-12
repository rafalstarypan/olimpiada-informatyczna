#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - II Stage
    Problem name: Zawody sportowe
    Problem link: https://szkopul.edu.pl/problemset/problem/fYzoFHo_2JRG4FQSt5UPRpn5/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e6+5;
const int M = 3e4+5;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

int n;
vector<int> G[2*MAX_N];
bool isRemoved[2*MAX_N];
int cand[MAX_N];
int ranking[MAX_N];
bool vis[2*MAX_N];

void dfs(int v) {
	vis[v] = true;
	for (int to: G[v]) {
		if (isRemoved[to]) continue;
		if (!vis[to]) dfs(to);
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
		
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char type; cin >> type;
		if (type == 'N') {
			int p1, p2;
			cin >> p1 >> p2;
			G[i+n].push_back(p1);
			G[i+n].push_back(p2);
			G[p1].push_back(i+n);
			G[p2].push_back(i+n);
			cand[i] = 2;
		} else {
			int p; cin >> p;
			G[i+n].push_back(p);
			G[p].push_back(i+n);
			cand[i] = 1;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (G[i].empty()) {
			cout << "NIE\n";
			cout << "0\n";
			return 0;
		}
	}
	
	queue<int> Q;
	for (int i = 1; i <= n; i++) {
		if (cand[i] == 1) Q.push(i+n);
	}
	int done = 0;
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		int myPlace = -1;
		for (int to: G[v]) {
			if (!isRemoved[to]) {
				myPlace = to;
				break;
			}
		}
		if (myPlace == -1) {
			cout << "NIE\n";
			cout << "0\n";
			return 0;
		}
		done++;
		ranking[v-n] = myPlace;
		isRemoved[v] = isRemoved[myPlace] = true;
		
		for (int to: G[myPlace]) {
			if (isRemoved[to]) continue;
			cand[to-n]--;
			if (cand[to-n] == 0) {
				cout << "NIE\n";
				cout << "0\n";
				return 0;
			}
			Q.push(to);
		}
	}
	
	if (done == n) {
		cout << "TAK\n";
		for (int i = 1; i <= n; i++) {
			cout << ranking[i] << '\n';
		}
		return 0;
	}
	
	ll ways = 1LL;
	for (int i = 1; i <= 2*n; i++) {
		if (isRemoved[i] || vis[i]) continue;
		dfs(i);
		
		ways *= 2;
		ways %= MOD;
 	}
	
	cout << "NIE\n";
	cout << ways << '\n';
	
    return 0;
}
