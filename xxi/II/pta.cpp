#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - II Stage
    Problem name: Ptaszek
    Problem link: https://szkopul.edu.pl/problemset/problem/A3QYXKEiRLgKerciOwA_lbCD/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e6+5;
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;

int n, k;
int a[MAX_N];
deque<PII> minQ;

void popMin(PII toRem) {
	if (minQ.front() == toRem) minQ.pop_front();
}

void addMin(int val, int height) {
	while (!minQ.empty()) {
		if (minQ.back().first > val) {
			minQ.pop_back();
			continue;
		}
		if (minQ.back().first == val && minQ.back().second < height) {
			minQ.pop_back();
			continue;
		}
		break;
	}
	minQ.push_back({val, height});
}

void solve() {
	minQ.clear();
	vector<int> dp(n+3, inf);
	dp[1] = 0;	
	minQ.push_back({0, a[1]});
	
	for (int i = 2; i <= n; i++) {
		if (i-k-1 >= 1) popMin(make_pair(dp[i-k-1], a[i-k-1]));
		
		int val = minQ.front().first;
		int height = minQ.front().second;
		if (height <= a[i]) val++;
		
		dp[i] = val;
		addMin(dp[i], a[i]);
	}
	
	cout << dp[n] << '\n';
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	int T; cin >> T;
	while (T--) {
		cin >> k;
		solve();
	}
	
	
    return 0;
}
