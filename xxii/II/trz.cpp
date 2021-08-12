#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXII OI - II Stage
    Problem name: Trzy wieze
    Problem link: https://szkopul.edu.pl/problemset/problem/Grfouq9u3g_TYktFXO2sNjCU/site/?key=statement
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
int pref[MAX_N][3];     // A B C
string s;

bool check(int a, int b) {
    return (a != b || a == 0 || b == 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'S') s[i] = 'A';
    }

    for (int i = 1; i <= n; i++) {
        pref[i][0] = pref[i-1][0];
        pref[i][1] = pref[i-1][1];
        pref[i][2] = pref[i-1][2];
        char c = s[i-1];
        pref[i][c-'A']++;
    }

    int ans = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = i; j <= n; j++) {
            int a = pref[j][0] - pref[i-1][0];
            int b = pref[j][1] - pref[i-1][1];
            int c = pref[j][2] - pref[i-1][2];
            if (check(a, b) && check(b, c) && check(a, c) && j-i+1 > ans) {
                ans = j-i+1;
            }
        }
    }

    for (int j = n; j >= n-2; j--) {
        for (int i = j; i >= 1; i--) {
            int a = pref[j][0] - pref[i-1][0];
            int b = pref[j][1] - pref[i-1][1];
            int c = pref[j][2] - pref[i-1][2];
            if (check(a, b) && check(b, c) && check(a, c) && j-i+1 > ans) {
                ans = j-i+1;
            }
        }
    }

    cout << ans;


    return 0;
}
