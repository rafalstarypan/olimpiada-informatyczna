#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXVII OI - II stage 
    Problem name: Marudny Bajtazar
    Problem link: https://szkopul.edu.pl/problemset/problem/kvwWom2nxVBqipEfeiMtidn5/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = (1 << 17);
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 2e9;
const ll MOD = 1000000007LL;

const int MAX_LEN = 17;

int n, Q;
string s;
int cnt[MAX_N + 5][MAX_LEN];
int sizes[MAX_LEN];

int query() {
    for (int len = 1; len < MAX_LEN; len++) {
        if (sizes[len] < (1 << len)) return len;
    }
    return MAX_LEN;
}

void addHashes(int start) {
    int curLen = 0;
    int curHash = 0;
    for (int i = start; i < min(n, start+MAX_LEN); i++) {
        if (s[i] == '1') {
            curHash += (1 << curLen);
        }
        curLen++;
        if (cnt[curHash][curLen] == 0) sizes[curLen]++;
        cnt[curHash][curLen]++;
    }
}

void removeHashes(int start) {
    int curLen = 0;
    int curHash = 0;
    for (int i = start; i < min(n, start+MAX_LEN); i++) {
        if (s[i] == '1') {
            curHash += (1 << curLen);
        }
        curLen++;
        cnt[curHash][curLen]--;
        if (cnt[curHash][curLen] == 0) sizes[curLen]--;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> Q >> s;

    for (int i = 0; i < n; i++) {
        addHashes(i);
    }

    cout << query() << "\n";

    for (int q = 0; q < Q; q++) {
        int pos; cin >> pos;
        pos--;

        for (int i = max(0, pos-16); i <= pos; i++) {
            removeHashes(i);
        }

        if (s[pos] == '0') s[pos] = '1';
        else s[pos] = '0';

        for (int i = max(0, pos-16); i <= pos; i++) {
            addHashes(i);
        }

        cout << query() << "\n";
    }


    return 0;
}
