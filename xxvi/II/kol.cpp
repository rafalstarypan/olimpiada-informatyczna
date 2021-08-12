#include<bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - II stage
	Problem name: Kolacje
	Problem link: https://szkopul.edu.pl/problemset/problem/CACYTyPO4YJxyZzNumr0zr5e/site/?key=statement

    The solution scores 69 points.
*/

typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<int, ll> PILL;
typedef pair<int, int> PII;
const int MAX_N = 1e5+5;
const ll INF = (ll)(1e18);

struct Query {
    int u;
    int v;
    int type;
};

class SparseTable {
public:
    int n;
    vector<vector<int>> sparseTable;
    vector<int> logTable;

    int pull(int x, int y) {       // function to merge intervals - it can be changed to 'max'
        return min(x, y);
    }

    void build(vector<int> a) {
        n = a.size();

        logTable.resize(n+1, 0);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i/2] + 1;
        }

        sparseTable.resize(logTable.back()+1, vector<int>(n));
        sparseTable[0] = a;

        for (int row = 1; row < sparseTable.size(); row++) {
            for (int i = 0; i + (1 << row) <= n; i++) {
                sparseTable[row][i] = pull(sparseTable[row-1][i], sparseTable[row-1][i+(1 << (row-1))]);
            }
        }
    }

    int query(int l, int r) {
        int theLog = logTable[r - l];
        int ret = pull(sparseTable[theLog][l], sparseTable[theLog][r - (1 << theLog)]);
        return ret;
    }
};

int n, r;
int nodeToType[MAX_N];      // the type of 'ith' node
vector<int> types[MAX_N];  // all nodes of type 'ri'
vector<PILL> G[MAX_N];
map<int, vector<PII>> mp;
map<PII, ll> ans[MAX_N];
vector<Query> queries;
vector<int> eulerTour;
ll dist[MAX_N];         // distance from the root
vector<int> timeToNode;
int firstEncounter[MAX_N];
SparseTable sparTab;

void dfs(int v, int par, ll lastEdge) {
    if (v == 1) dist[v] = 0LL;
    else dist[v] = dist[par] + lastEdge;

    int newTime = timeToNode.size();
    firstEncounter[v] = eulerTour.size();
    timeToNode.push_back(v);
    eulerTour.push_back(newTime);

    for (auto e: G[v]) {
        int to = e.first;
        ll cost = e.second;
        if (to == par) continue;
        dfs(to, v, cost);
        eulerTour.push_back(newTime);
    }
}

ll getDist(int u, int v) {
    int l = min(firstEncounter[u], firstEncounter[v]);
    int r = max(firstEncounter[u], firstEncounter[v]);
    int lca = timeToNode[sparTab.query(l, r+1)];
    ll ret = dist[u] + dist[v] - 2*dist[lca];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> r;
    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        types[t].push_back(i);
        nodeToType[i] = t;
    }

    for (int i = 0; i < n-1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    dfs(1, -1, 0LL);

    sparTab.build(eulerTour);

    if (r == 1) {
        int Q;
        cin >> Q;
        while (Q--) {
            int u, v, t;
            cin >> u >> v >> t;
            cout << getDist(u, v) << "\n";
        }
        return 0;
    }

    int Q; cin >> Q;
    while (Q--) {
        int u, v, t;
        cin >> u >> v >> t;
        if (nodeToType[u] == nodeToType[v] && nodeToType[u] == t) {
            ans[t][{u,v}] = getDist(u, v);
            queries.push_back({u, v, t});
            continue;
        }
        mp[t].push_back({u, v});
        queries.push_back({u, v, t});
    }

    for (auto it: mp) {
        int t = it.first;
        vector<PII> vec = it.second;
        for (auto rest: types[t]) {
            for (auto p: vec) {
                int u = p.first;
                int v = p.second;
                ll d = getDist(u, rest) + getDist(v, rest);
                if (ans[t].find(p) == ans[t].end() || d < ans[t][p]) {
                    ans[t][p] = d;
                }
            }
        }
    }

    for (int i = 0; i < queries.size(); i++) {
        int t = queries[i].type;
        int u = queries[i].u;
        int v = queries[i].v;
        if (ans[t].empty()) {
            cout << "-1\n";
        } else {
            cout << ans[t][{u, v}] << "\n";
        }
    }







    return 0;
}
