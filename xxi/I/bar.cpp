#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - I Stage
    Problem name: Bar salatkowy
    Problem link: https://szkopul.edu.pl/problemset/problem/7xybSzndMlQ8nWLZZsMTcM9C/site/?key=statement
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

int n;
string s;
int pref[MAX_N], smaller[MAX_N];
unordered_map<int, vector<int>> mp;
PII t[4*MAX_N];

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = {pref[l], l};
        return;
    }

    int mid = (l+r) / 2;
    build(2*v, l, mid);
    build(2*v+1, mid+1, r);

    if (t[2*v].first > t[2*v+1].first) {
        t[v] = t[2*v];
    } else {
        t[v] = t[2*v+1];
    }
}

PII query(int v, int l, int r, int qL, int qR) {
    PII result = {-inf, 0};
    if (qL > r || qR < l) return result;

    if (qL <= l && r <= qR) {
        return t[v];
    }

    int mid = (l+r) / 2;
    PII left = query(2*v, l, mid, qL, qR);
    PII right = query(2*v+1, mid+1, r, qL, qR);

    if (left.first > right.first) {
        result = left;
    } else {
        result = right;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;
    s = '#' + s;

    for (int i=1; i<=n; i++) {
        if (s[i] == 'j') {
            pref[i] = pref[i-1] - 1;
        } else {
            pref[i] = pref[i-1] + 1;
        }
    }

    for (int i=1; i<=n; i++) {
        int val = pref[i-1];
        int cur = pref[i];
        if (s[i] != 'j') mp[val].push_back(i);
        if (!mp[cur+1].empty()) {
            for (auto x: mp[cur+1]) {
                smaller[x] = i-1;
            }
            mp[cur+1].clear();
        }
    }

    for (auto x: mp) {
        for (auto y: x.second) {
            smaller[y] = n;
        }
    }

    build(1, 1, n);

    int ans = 0;
    for (int i=1; i<=n; i++) {
        if (s[i] == 'j') continue;
        PII p = query(1, 1, n, i, smaller[i]);
        int len = query(1, 1, n, i, smaller[i]).second - i + 1;
        ans = max(ans, len);
    }

    cout << ans;

    return 0;
}
