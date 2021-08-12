#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - I Stage
    Problem name: Podzielnosc
    Problem link: https://szkopul.edu.pl/problemset/problem/cSnlafnvkbirhnQrS9CQ9MEw/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e6+5;

ll B;
int Q;
ll digits[MAX_N];
ll pref[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> B >> Q;
    for (int i=0; i<B; i++) {
        cin >> digits[i];
    }

    ll sum = 0;
    for (int i=0; i<B; i++) {
        ll tmp = (ll)i;
        sum += digits[i] * tmp;
    }
    ll r = sum % (B-1);
    if (r != 0) {
        digits[r]--;
    }

    pref[0] = digits[0];
    for (int i=1; i<B; i++) {
        pref[i] = pref[i-1] + digits[i];
    }

    while (Q--) {
        ll k;
        cin >> k;
        if (k >= pref[B-1]) {
            cout << -1 << "\n";
            continue;
        }
        int ans = upper_bound(pref, pref+B, k) - pref;
        cout << ans << "\n";
    }

    return 0;
}
