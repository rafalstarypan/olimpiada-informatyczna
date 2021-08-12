#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXII OI - I Stage
    Problem name: Kinoman
    Problem link: https://szkopul.edu.pl/problemset/problem/k-RYEjhwNTo_XdaCidXQUGMU/site/?key=statement
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

int n, m;
int f[MAX_N];
ll w[MAX_N], p[MAX_N];
vector<int> indexes[MAX_N];
PLL t[4*MAX_N];

void build(int v, int l, int r) {
    if (l == r) {
        t[v].first = t[v].second = p[l];
        return;
    }

    int mid = (l+r) / 2;
    build(2*v, l, mid);
    build(2*v+1, mid+1, r);

    t[v].first = t[2*v].first + t[2*v+1].first;
    t[v].second = max(t[2*v].second, t[2*v].first + t[2*v+1].second);
}

void update(int v, int l, int r, int pos, ll val) {
    if (pos < l || pos > r) return;

    if (l == pos && r == pos) {
        t[v].first = t[v].second = val;
        return;
    }

    int mid = (l+r) / 2;
    update(2*v, l, mid, pos, val);
    update(2*v+1, mid+1, r, pos, val);

    t[v].first = t[2*v].first + t[2*v+1].first;
    t[v].second = max(t[2*v].second, t[2*v].first + t[2*v+1].second);
}

PLL query(int v, int l, int r, int qL, int qR) {
    PLL result = {0, 0};
    if (r < qL || l > qR) {
        return result;
    }

    if (qL <= l && r <= qR) {
        return t[v];
    }

    int mid = (l+r) / 2;
    PLL left = query(2*v, l, mid, qL, qR);
    PLL right = query(2*v+1, mid+1, r, qL, qR);

    result.first = left.first + right.first;
    result.second = max(left.second, left.first + right.second);

    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> f[i];
    }
    for (int i=1; i<=m; i++) {
        cin >> w[i];
    }

    for (int i=n; i>=1; i--) {
        indexes[f[i]].push_back(i);
    }

    for (int i=1; i<=m; i++) {
        if (!indexes[i].empty()) {
            int tmp = indexes[i].back();
            p[tmp] = w[i];
        }
        if (indexes[i].size() > 1) {
            int s = indexes[i].size();
            int tmp = indexes[i][s-2];
            p[tmp] = -w[i];
        }
    }

    build(1, 1, n);

    ll ans = 0LL;
    for (int i=1; i<=n; i++) {
        ll cur = query(1, 1, n, i, n).second;
        ans = max(ans, cur);

        int film = f[i];
        update(1, 1, n, i, 0);
        indexes[film].pop_back();

        if (!indexes[film].empty()) {
            int pos = indexes[film].back();
            update(1, 1, n, pos, w[film]);
        }

        if (indexes[film].size() > 1) {
            int s = indexes[film].size();
            int pos = indexes[film][s-2];
            update(1, 1, n, pos, -w[film]);
        }

    }

    cout << ans;

    return 0;
}
