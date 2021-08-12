#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - II stage
	Problem name: Gwiazdy
	Problem link: https://szkopul.edu.pl/problemset/problem/vE94xK5yr-lSfcAMD3IKFd7F/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<int, ll> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 5e5+5;
const int M = 15000;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

int n, s;
ll L[MAX_N], R[MAX_N];
deque<char> dir;
bool swapped = false;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	cin >> n >> s;
	for (int i = 1; i < n; i++) {
		cin >> L[i] >> R[i];
	}
	
	if (R[1] < L[1]) {
		swapped = true;
		for (int i = 1; i < n; i++) {
			swap(L[i], R[i]);
		}
		s = n - s + 1;
	}
	
	ll ans = 0LL;
	for (int i = 1; i < n; i++) {
		if (L[i] <= R[i]) {
			dir.push_back('L');
			ans += L[i];
		}
		else {
			dir.push_back('R');
			ans += R[i];
		}
	}
	
	ll minCost = INF;
	int pos = -1;
	for (int i = 0; i < s; i++) {
		// no change needed
		if (dir[i] == 'R') {
			pos = -1;
			break;
		}
		if (R[i+1] - L[i+1] < minCost) {
			minCost = R[i+1] - L[i+1];
			pos = i;
		}
	}
	
	if (pos != -1) {
		ans += minCost;
		dir[pos] = 'R';
	}
	
	vector<int> res;
	res.push_back(s);
	int curL = 1;
	int curR = n;
	if (curL == s) curL++;
	if (curR == s) curR--;
	
	while (!dir.empty()) {
		char curDir = dir.front();
		int cnt = 0;
		while (!dir.empty() && dir.front() == curDir) {
			cnt++;
			dir.pop_front();
		}
		
		if (curDir == 'L') {
			int nxt = curL + cnt - 1;
			if (curL <= s && s <= nxt) nxt++;
			for (int i = nxt; i >= curL; i--) {
				if (i != s) res.push_back(i);
			}
			curL = nxt + 1;
		}
		
		if (curDir == 'R') {
			int nxt = curR - cnt + 1;
			if (nxt <= s && s <= curR) nxt--;
			for (int i = nxt; i <= curR; i++) {
				if (i != s) res.push_back(i);
			}
			curR = nxt - 1;
		}
	}
	
	cout << ans << '\n';
	for (int x: res) {
		if (swapped) {
			cout << n - x + 1 << ' ';
		} else {
			cout << x << ' ';
		}
	}
	cout << '\n';
	
    return 0;
}
