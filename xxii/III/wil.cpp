#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXII OI - III Stage
    Problem name: Wilcze doly
    Problem link: https://szkopul.edu.pl/problemset/problem/07Q0fFk7fU2TmGr6wpPeDCZj/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 2e6+5;
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;

int n, d, leaves;
ll p;
ll arr[MAX_N], pref[MAX_N], t[4*MAX_N];

ll query(int l, int r) {
    int vL = l + leaves - 1;
    int vR = r + leaves - 1;
    ll ans = max(t[vL], t[vR]);

    while (vL/2 != vR/2) {
        if (vL%2 == 0) {
            ans = max(ans, t[vL+1]);
        }
        if (vR%2 == 1) {
            ans = max(ans, t[vR-1]);
        }
        vL /= 2;
        vR /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> p >> d;
    leaves = 1;
    while (leaves < n-d+1) leaves *= 2;

    pref[0] = 0LL;
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
        pref[i] = pref[i-1] + arr[i];
    }

    int index = d;
    for (int i=0; i<leaves; i++) {
        t[i+leaves] = pref[index] - pref[index-d];
        index++;
    }
    for (int i=leaves-1; i>=1; i--) {
        t[i] = max(t[2*i], t[2*i+1]);
    }

    int ans = d;
    int j = d;
    for (int i=1; i<=n-d+1; i++) {
        j = max(j, i+d-1);
        while (j+1 <= n && (pref[j+1] - pref[i-1]) - query(i, j-d+2) <= p) j++;
        ans = max(ans, j-i+1);
    }

    cout << ans;

    return 0;
}
