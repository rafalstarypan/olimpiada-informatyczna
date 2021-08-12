#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXV OI - II Stage
	Problem name: Przekazniki telekomunikacyjne
	Problem link: https://szkopul.edu.pl/problemset/problem/GmAagCBetbskP0qiKlgVd-6A/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 3e5+5;
const int M = 3e4+5;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

int n, Q;

PII maszt[MAX_N];

ll A[4*MAX_N];
ll R[4*MAX_N];
ll tree[4*MAX_N];

void push(int v, int l, int r) {
	int mid = (l+r) / 2;
	int mul = (mid - l + 1);
	
	A[2*v] += A[v];
	R[2*v] += R[v];
	
	A[2*v+1] += A[v];
	A[2*v+1] += R[v] * mul;
	R[2*v+1] += R[v];
	
	ll len = (ll)(mid - l);
	ll last = A[v] + len * R[v];
	ll tmp = (A[v] + last) * (len+1);
	tmp /= 2;
	tree[2*v] += tmp;
	
	len = (ll)(r - mid - 1);
	ll a1 = A[v] + mul * R[v];
	last = a1 + len * R[v];
	tmp = (a1 + last) * (len+1);
	tmp /= 2;
	tree[2*v+1] += tmp;
	
	A[v] = R[v] = 0LL;
}

void update(int v, int l, int r, int qL, int qR, ll deltaA, ll deltaR) {
	if (l > qR || r < qL) return;
	if (qL <= l && r <= qR) {
		int mul = l - qL;
		ll a1 = deltaA + deltaR * mul;
		A[v] += a1;
		R[v] += deltaR;
		
		ll len = (ll)(r - l);
		ll last = a1 + len * deltaR;
		ll tmp = (a1 + last) * (len+1);
		tmp /= 2;
		tree[v] += tmp;
		return;
	}
	
	push(v, l, r);
	int mid = (l+r) / 2;
	update(2*v, l, mid, qL, qR, deltaA, deltaR);
	update(2*v+1, mid+1, r, qL, qR, deltaA, deltaR);
	
	tree[v] = tree[2*v] + tree[2*v+1];
}

ll query(int v, int l, int r, int qL, int qR) {
	if (l > qR || r < qL) return 0LL;
	if (qL <= l && r <= qR) return tree[v];
	
	push(v, l, r);
	int mid = (l+r) / 2;
	
	return query(2*v, l, mid, qL, qR) + query(2*v+1, mid+1, r, qL, qR);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> Q;
	for (int qq = 0; qq < Q; qq++) {
		char type; cin >> type;
		if (type == 'P') {
			int x; int s, a;
			cin >> x >> s >> a;
			maszt[x] = make_pair(s, a);
			int d = s / a;
			int l = max(1, x - d);
			int r = min(n, x + d);
			ll deltaA = s - (ll)a * (x - l);
			update(1, 1, n, l, x, deltaA, a);
			if (x+1 <= r) update(1, 1, n, x+1, r, s - a, -a);
		} else if (type == 'U') {
			int x; cin >> x;
			int s = maszt[x].first;
			int a = maszt[x].second;
			int d = s / a;
			int l = max(1, x - d);
			int r = min(n, x + d);
			ll deltaA = s - (ll)a * (x - l);
			update(1, 1, n, l, x, -deltaA, -a);
			if (x+1 <= r) update(1, 1, n, x+1, r, a - s, a);
		} else {
			int qL, qR;
			cin >> qL >> qR;
			ll len = (ll)(qR - qL + 1);
			cout << query(1, 1, n, qL, qR) / len << '\n';
		}
	}
	
	
	
	
    return 0;
}
