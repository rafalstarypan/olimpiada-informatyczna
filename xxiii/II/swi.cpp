#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIII OI - II Stage
    Problem name: Swiateczny lancuch
    Problem link: https://szkopul.edu.pl/problemset/problem/cSa80AKpjHR8FlWE4BCpLGT3/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 5e5+5;
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;

int n, m;
int dsu[MAX_N], sizes[MAX_N];
int comp;

void reset() {
    comp = n;
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int doFind(int v) {
    if (v == dsu[v]) return v;
    return dsu[v] = doFind(dsu[v]);
}

bool doUnion(int u, int v) {
    int rootU = doFind(u);
    int rootV = doFind(v);
    if (rootU == rootV) return false;

    if (sizes[rootU] > sizes[rootV]) swap(rootU, rootV);
    sizes[rootV] += sizes[rootU];
    dsu[rootU] = rootV;

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    reset();

    for (int i = 0; i < m; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        for (int j = 0; j < l; j++) {
            if (doUnion(a, b)) comp--;
            a++; b++;
        }
    }

    cout << comp << '\n';

    return 0;
}