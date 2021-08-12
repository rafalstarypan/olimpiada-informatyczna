#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXII OI - II Stage
    Problem name: Logistyka
    Problem link: https://szkopul.edu.pl/problemset/problem/ShrCwRqlzMKLBb269GkVbWg_/site/?key=statement
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

struct Query {
	char type;
	int a;
	ll b;
};

int n, Q;
vector<Query> queries;
vector<ll> compress;
int cur = 1;
map<ll, int> valToPos;
ll arr[MAX_N];

const int LOG = 20;
const int BASE = (1 << LOG);
ll sum[2*BASE+5];
int cnt[2*BASE+5];

void update(int pos, ll deltaSum, int deltaCnt) {
	pos += BASE - 1;
	sum[pos] += deltaSum;
	cnt[pos] += deltaCnt;
	pos /= 2;
	
	while (pos) {
		sum[pos] = sum[2*pos] + sum[2*pos+1];
		cnt[pos] = cnt[2*pos] + cnt[2*pos+1];
		pos /= 2;
	}
}

ll querySum(int l, int r) {
	ll res = 0LL;
	l += BASE - 2;
	r += BASE;
	
	while (r-l > 1) {
		if (l%2 == 0) res += sum[l+1];
		if (r%2 == 1) res += sum[r-1];
		l /= 2; r /= 2;
	}
	return res;
}

int queryCnt(int l, int r) {
	int res = 0;
	l += BASE - 2;
	r += BASE;
	
	while (r-l > 1) {
		if (l%2 == 0) res += cnt[l+1];
		if (r%2 == 1) res += cnt[r-1];
		l /= 2; r /= 2;
	}
	return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
		
	cin >> n >> Q;
	for (int qq = 0; qq < Q; qq++) {
		char type; int a; ll b;
		cin >> type >> a >> b;
		queries.push_back({type, a, b});
		compress.push_back(b);
	}
	
	compress.push_back(0LL);
	sort(compress.begin(), compress.end());
	auto it = unique(compress.begin(), compress.end());
	compress.resize(distance(compress.begin(), it));
	
	for (ll i: compress) {
		valToPos[i] = cur;
		cur++;
	}
	
	update(1, 0LL, n);
	
	for (int qq = 0; qq < Q; qq++) {
		if (queries[qq].type == 'U') {
			int pos = queries[qq].a;
			ll len = queries[qq].b;
			
			int now = valToPos[arr[pos]];
			update(now, -arr[pos], -1);
			
			now = valToPos[len];
			update(now, len, 1);
			arr[pos] = len;
			
		} else {
			int c = queries[qq].a;
			ll S = queries[qq].b;
			int pos = valToPos[S];
			
			ll driverSum = querySum(1, pos);
			int driverCnt = queryCnt(pos+1, cur);
			
			ll total = driverSum + S * (ll)driverCnt;
			ll wanted = (ll)c * S;
			
			if (total >= wanted) {
				cout << "TAK\n";
			} else {
				cout << "NIE\n";
			}
		}
	}
	
	
    return 0;
}
