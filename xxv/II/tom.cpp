#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXV OI - II Stage
	Problem name: Tomik poezji
	Problem link: https://szkopul.edu.pl/problemset/problem/Hhip15j-8Ro2dOb_4oB98C-G/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<int, ll> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e6+5;
const int M = 15000;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000009LL;

int n, s;
int a[MAX_N];
vector<int> pos[MAX_N];

void brute_force() {
	vector<int> vec;
	for (int i = 1; i <= n; i++) {
		vec.push_back(i);
	}
	
	int ans = inf;
	vector<int> res;
	
	do {
		int cur = 0;
		int tmp = 0;
		for (int i = 0; i < n-1; i++) {
			cur += a[vec[i]];
			cur %= s;
			if (cur == s-1) {
				tmp++;
				cur = 0;
			}
		}
		if (ans > tmp) {
			ans = tmp;
			res = vec;
		}
		
	} while (next_permutation(vec.begin(), vec.end()));
	
	cout << ans << '\n';
	for (int i: res) {
		cout << i << ' ';
	}
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
		
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = (a[i] + 1) % s;
		pos[a[i]].push_back(i);
	}
	
	if (n <= 10) {
		brute_force();
		return 0;
	}
	
	int ans = 0;
	vector<int> res = pos[0];
	set<PII> secik;
	
	for (int i = 1; i < s; i++) {
		if (!pos[i].empty()) secik.insert({(int)pos[i].size(), i});
	}
	
	int cur = 0;
	while (!secik.empty()) {
		PII best = *secik.rbegin();
		secik.erase(best);
		int cnt = best.first;
		int who = best.second;
		
		if ((cur + who) % s != s-1) {
			cur = (cur + who) % s;
			res.push_back(pos[who].back());
			pos[who].pop_back();
			if (cnt > 1) secik.insert({cnt-1, who});
			continue;
		}
		
		if (!secik.empty()) {
			PII nxt = *secik.rbegin();
			secik.erase(nxt);
			cnt = nxt.first;
			who = nxt.second;
			cur = (cur + who) % s;
			res.push_back(pos[who].back());
			pos[who].pop_back();
			if (cnt > 1) secik.insert({cnt-1, who});
			secik.insert(best);
			continue;
		}
		
		cur = (cur + who) % s;
		res.push_back(pos[who].back());
		pos[who].pop_back();
		if (cnt > 1) {
			if (cur == s-1) {
				ans++;
				cur = 0;
			}
			secik.insert({cnt-1, who});
		}
	}
	
	cout << ans << '\n';
	for (int i: res) {
		cout << i << ' ';
	}
	cout << '\n';
	
    return 0;
}
