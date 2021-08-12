#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXVII OI - I stage 
    Problem: Pomniejszenie
    Problem link: https://szkopul.edu.pl/problemset/problem/K7FKfwLplcsjx-o-BYnJq3b1/site/?key=statement
*/

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<int, bool> PIB;
const int MAX_N = 1e4+5;
const int inf = 1e9;

string A, B;
int n, k;

string construct(int smaller, char c, int cost) {
    string ans;
    if (smaller == 0) ans = "";
    else ans = B.substr(0, smaller);

    ans += c;
    int i = smaller+1;
    while (i < n) {
        int suff = n - i;
        if (cost == k) break;
        if (A[i] == '9' && cost+suff <= k) {
            cost++;
            ans += '8';
        } else if (A[i] != '9'){
            ans += '9';
            cost++;
        } else {
            ans += A[i];
        }
        i++;
    }

    while (i < n) {
        ans += A[i];
        i++;
    }
    return ans;
}

void solve() {
    cin >> A >> B >> k;
    n = A.size();
    vector<int> pref(n, 0);
    if (A[0] != B[0]) pref[0] = 1;
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i-1];
        if (A[i] != B[i]) pref[i]++;
    }

    for (int i = n-1; i >= 0; i--) {
        int maxDigit = B[i] - '0';
        int curA = A[i] - '0';
        int suff = n - i - 1;
        for (int j = maxDigit-1; j >= 0; j--) {
            int cost = 0;
            if (i > 0) cost += pref[i-1];
            if (j != curA) cost++;
            if (cost+suff >= k && cost <= k) {
                char c = j+'0';
                cout << construct(i, c, cost) << "\n";
                return;
            }
        }
    }

    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }


    return 0;
}