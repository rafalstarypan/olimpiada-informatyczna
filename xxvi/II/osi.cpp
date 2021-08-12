#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - II stage
	Problem name: Osiedla
	Problem link: https://szkopul.edu.pl/problemset/problem/nldsb4EW1YuZykBlf4lcZL1Y/site/?key=statement
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
vector<PII> G[MAX_N];
vector<PII> edges;
int mp[MAX_N];          // direction for edge of index 'i'
bool vis[MAX_N];
set<int> bridges;
int id = 0;
int ids[MAX_N], lows[MAX_N];
int ans = 0;

void dfs(int v, int par) {
    vis[v] = true;
    id++;
    lows[v] = ids[v] = id;
    bool skipPar = true;
    for (auto e: G[v]) {
        int to = e.first;
        int ind = e.second;
        if (to == par && skipPar) {
            skipPar = false;
            continue;
        }
        if (!vis[to]) {
            dfs(to, v);
            lows[v] = min(lows[v], lows[to]);
            if (ids[v] < lows[to]) {
                bridges.insert(ind);
            }
        } else {
            lows[v] = min(lows[v], ids[to]);
        }
    }
}


void findBridges() {
    for  (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
}

void finalDfs(int v, int par) {
    vis[v] = true;
    bool skipPar = true;
    for (auto e: G[v]) {
        int to = e.first;
        int ind = e.second;
        if (to == par && skipPar) {
            skipPar = false;
            continue;
        }
        if (!vis[to]) {
            if (v == edges[ind].first) {
                mp[ind] = 1;
            } else {
                mp[ind] = -1;
            }
            finalDfs(to, v);
        } else {
            if (mp[ind] == 0) {
                if (v == edges[ind].first) {
                    mp[ind] = 1;
                } else {
                    mp[ind] = -1;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        edges.push_back({x, y});
        G[x].push_back({y, i});
        G[y].push_back({x, i});
    }

    findBridges();
    for (auto b: bridges) {
        mp[b] = 1;
    }

    for (int i = 1; i <= n; i++) {
        vis[i] = false;
        G[i].clear();
    }

    for (int i = 0; i < edges.size(); i++) {
        if (bridges.find(i) != bridges.end()) continue;
        int u = edges[i].first;
        int v = edges[i].second;
        G[u].push_back({v, i});
        G[v].push_back({u, i});
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans++;
            finalDfs(i, -1);
        }
    }

    cout << ans << "\n";
    for (int i = 0; i < m; i++) {
        if (mp[i] == 1) {
            cout << '>';
        } else if (mp[i] == -1) {
            cout << '<';
        } else {
            cout << '0';
        }
    }


    return 0;
}
