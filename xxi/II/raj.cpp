#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - II Stage
    Problem name: Rajd
    Problem link: https://szkopul.edu.pl/problemset/problem/orur2kPvWQR0LzMXXoP6pCat/site/?key=statement
*/

typedef pair<int, int> PII;
typedef long long ll;

const int MAX_N = 5e5+5;
const int M = 1e6+5;
const int inf = 1e9;

int n, m;
vector<int> G[MAX_N];
vector<PII> edges;
int inDeg[MAX_N];
int toTopSort[MAX_N];  // mapuje numery wierzcholkow na numery po topsorcie
int toVertex[MAX_N];
int cur = 1;
int start[MAX_N], before[MAX_N];
int stop[MAX_N], after[MAX_N];

int t[4*MAX_N];

void update(int v, int l, int r, int qL, int qR, int val) {
    if (qL <= l && r <= qR) {
        t[v] = max(t[v], val);
        return;
    }
    if (qL > r || qR < l) return;
    int mid = (l+r) / 2;
    update(2*v, l, mid, qL, qR, val);
    update(2*v+1, mid+1, r, qL, qR, val);
}

int query(int v, int l, int r, int pos) {
    if (l == pos && r == pos) {
        return t[v];
    }
    int mid = (l+r) / 2;
    if (pos <= mid) {
        int leftSub = query(2*v, l, mid, pos);
        return max(t[v], leftSub);
    } else {
        int rightSub = query(2*v+1, mid+1, r, pos);
        return max(t[v], rightSub);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        inDeg[v]++;
        edges.push_back({u, v});
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDeg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        toTopSort[v] = cur;
        toVertex[cur] = v;
        cur++;
        for (auto to: G[v]) {
            inDeg[to]--;
            if (inDeg[to] == 0) {
                q.push(to);
            }
        }
    }

    stop[1] = 0;
    for (int i = 1; i <= n; i++) {
        int v = toVertex[i];
        for (auto to: G[v]) {
            int x = toTopSort[to];
            stop[x] = max(stop[x], stop[i] + 1);
        }
    }
    for (int i = 2; i <= n; i++) {
        before[i] = max(before[i-1], stop[i]);
    }

    start[n] = 0;
    for (int i = n-1; i >= 1; i--) {
        int v = toVertex[i];
        for (auto to: G[v]) {
            int x = toTopSort[to];
            start[i] = max(start[i], start[x] + 1);
        }
    }

    for (int i = n-1; i >= 1; i--) {
        after[i] = max(after[i+1], start[i]);
    }

    for (PII p: edges) {
        int u = p.first;
        int v = p.second;
        int a = min(toTopSort[u], toTopSort[v]);
        int b = max(toTopSort[u], toTopSort[v]);
        if (a+1 == b) continue;
        int dist = stop[a] + 1 + start[b];
        update(1, 1, n, a+1, b-1, dist);
    }

    int len = inf;
    int chosenVertex = -1;
    vector<int> vec;
    for (int i = 1; i <= n; i++) {
        int tmp = query(1, 1, n, i);
        int path = max({tmp, before[i-1], after[i+1]});
        if (path < len) {
            chosenVertex = toVertex[i];
            len = path;
        }
    }

    cout << chosenVertex << " " << len << "\n";


    return 0;
}
