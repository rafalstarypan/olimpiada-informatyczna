#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - III stage
	Problem name: Wyscigi
	Problem link: https://szkopul.edu.pl/problemset/problem/S8phA644ooC9arh6FhXzvbiH/site/?key=statement

	The solution scores 50 points.
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 3e5+5;
const int M = 3e4+5;
const ll INF = (ll)(2e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

int n, Q;
ll a[MAX_N];

const int LOG = 19;
const int BASE = (1 << LOG);
int tree[2*BASE+5];

void updatePoints(int l, int r, ll val) {
	l += BASE - 2;
	r += BASE;
	
	while (r-l > 1) {
		if (l%2 == 0) {
			tree[l+1] += val;
		}
		if (r%2 == 1) {
			tree[r-1] += val;
		}
		l /= 2; r /= 2;
	}
}

ll queryPoints(int pos) {
	pos += BASE - 1;
	ll res = 0LL;
	while (pos) {
		res += tree[pos];
		pos /= 2;
	}
	return res;
}

ll T[4*MAX_N];
ll lazy[4*MAX_N];

void push(int v) {
	lazy[2*v] += lazy[v];
	lazy[2*v+1] += lazy[v];
	T[2*v] += lazy[v];
	T[2*v+1] += lazy[v];
	lazy[v] = 0LL;
}

void updateScore(int v, int l, int r, int qL, int qR, ll val) {
	if (l > qR || r < qL) return;
	if (qL <= l && r <= qR) {
		T[v] += val;
		lazy[v] += val;
		return;
	}
	
	push(v);
	int mid = (l+r) / 2;
	updateScore(2*v, l, mid, qL, qR, val);
	updateScore(2*v+1, mid+1, r, qL, qR, val);

	T[v] = max(T[2*v], T[2*v+1]);
}

ll queryScore(int v, int l, int r, int qL, int qR) {
	if (l > qR || r < qL) return -INF;
	if (qL <= l && r <= qR) return T[v];
	int mid = (l+r) / 2;
	push(v);
	return max(queryScore(2*v, l, mid, qL, qR), queryScore(2*v+1, mid+1, r, qL, qR));
}

int findPrefix(ll x) {
	int lo = 1;
	int hi = n;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (queryPoints(mid) >= x) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	if (queryPoints(lo) >= x) return lo;
	return -1;
}

int findSuffix(ll x) {
	int lo = 1;
	int hi = n;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (queryPoints(mid) <= x) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	if (queryPoints(lo) <= x) return lo;
	return -1;
}

int countWinners() {
	int lo = 1;
	int hi = n;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		ll curPoints = queryPoints(mid) + n;
		if (mid < n) {
			updateScore(1, 1, n, mid+1, n, -1LL);
		}
		
		ll before = -INF;
		if (mid > 1) before = queryScore(1, 1, n, 1, mid - 1);
		
		ll after = -INF;
		if (mid < n) after = queryScore(1, 1, n, mid + 1, n);
		
		if (curPoints >= before && curPoints >= after) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
		
		if (mid < n) {
			updateScore(1, 1, n, mid+1, n, 1LL);
		}
	}
	return lo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> Q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	sort(a + 1, a + 1 + n);
	reverse(a + 1, a + 1 + n);
	
	for (int i = 1; i <= n; i++) {
		updatePoints(i, i, a[i]);
		updateScore(1, 1, n, i, i, a[i] + i);
	}
	
	for (int qq = 0; qq < Q; qq++) {
		char type; cin >> type;
		if (type == 'B') {
			ll x, y;
			cin >> x >> y;
			int pos = findPrefix(x);
			if (pos != -1) {
				updatePoints(1, pos, y);
				updateScore(1, 1, n, 1, pos, y);
			}
		} else if (type == 'K') {
			ll x, y;
			cin >> x >> y;
			int pos = findSuffix(x);
			if (pos != -1) {
				updatePoints(pos, n, -y);
				updateScore(1, 1, n, pos, n, -y);
			}
		} else {
			cout << countWinners() << '\n';
		}
	}
	
	
    return 0;
}
