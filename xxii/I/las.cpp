#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXII OI - I Stage
    Problem name: Lasuchy
    Problem link: https://szkopul.edu.pl/problemset/problem/Hj7Ko64-xPs_FrzJ4WucMde9/site/?key=statement
*/

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<int, bool> PIB;
const int MAX_N = 1e4+5;
const int inf = 1e9;

int n;
vector<int> a, ans;

int nxt(int i) {
    return (i+1)%n;
}

int prv(int i) {
    if (i == 0) return n-1;
    return (i-1)%n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    a.resize(n);
    ans.resize(n, -1);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] *= 2;
    }
    for (int i = 0; i < n; i++) {
        ans[i] = i;
    }

    for (int rep = 0; rep < 2; rep++) {
    for (int i = 0; i < n; i++) {
        int l, r;
        if (ans[prv(i)] == i) l = a[i] / 2;
        else l = a[i];
        if (ans[nxt(i)] == nxt(i)) r = a[nxt(i)] / 2;
        else r = a[nxt(i)];
        if (l >= r) {
            ans[i] = i;
        } else {
            ans[i] = nxt(i);
        }
    }

    for (int i = n-1; i >= 0; i--) {
        int l, r;
        if (ans[prv(i)] == i) {
            l = a[i] / 2;
        } else {
            l = a[i];
        }
        if (ans[nxt(i)] == nxt(i)) r = a[nxt(i)] / 2;
        else r = a[nxt(i)];
        if (l >= r) {
            ans[i] = i;
        } else {
            ans[i] = nxt(i);
        }
    }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";

    return 0;
}
