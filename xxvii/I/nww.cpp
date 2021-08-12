#include <bits/stdc++.h>
using namespace std;

/*  
    Author: Rafal Starypan
    Contest: XXVII OI - I stage 
    Problem: Najmniejsza wspolna wielokrotnosc
    Problem link: https://szkopul.edu.pl/problemset/problem/nYCgpBEkq_hw9S-QaoEOOKCI/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e5+5;
const ll SLOW = (ll)(1e9);
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;
const ll UPPER = 1500000LL;

vector<ll> queries;
ll maxQuery = -INF;
map<ll, PLL> mp;

ll lcm(ll a, ll b) {
    ll gcd = __gcd(a, b);
    ll ret = a / gcd;
    return ret * b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        ll M;
        cin >> M;
        maxQuery = max(maxQuery, M);
        queries.push_back(M);
        mp[M] = {-1, -1};
    }

    for (ll i = 1LL; i <= UPPER; i++) {
        ll inLcm = i;
        for (ll j = 1LL; j <= 60; j++) {
            ll tmp = i+j;
            inLcm = lcm(inLcm, tmp);
            if (inLcm > INF) break;
            if (mp.find(inLcm) != mp.end() && mp[inLcm].first == -1) {
                mp[inLcm] = {i, tmp};
            }
        }
    }

    for (int i = 0; i < T; i++) {
        ll M = queries[i];
        ll x = sqrt((double)M);
        ll y = x+1;
        if (x*y == M && mp[M].first == -1) {
            mp[M] = {x, y};
        }
        PLL p = mp[M];
        if (p.first == -1) {
            cout << "NIE\n";
        } else {
            cout << p.first << " " << p.second << "\n";
        }
    }



    return 0;
}