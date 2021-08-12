#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXVII OI - II stage 
    Problem name: Wakacje Bajtazara
    Problem link: https://szkopul.edu.pl/problemset/problem/pXcijJbDyC_jRAjkoxBH9sCO/site/?key=statement
*/

/*  Solution idea:
    Do dp[v][2] - max score going down from 'v' if 'v' is not taken / taken
    While calculating dp remember where the answer comes from
    CONSIDER THE CASE WHERE 'v' IS THE LCA OF A PATH
    After calculating dp find the endpoint of the best path
    Do another dp used in the brute force solution starting in the endpoint and use it to restore the answer
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

// General stuff

int n;
ll w[MAX_N];
vector<int> G[MAX_N];

// Stuff needed to compute the answer and find the root

ll dp[MAX_N][2];    // 0 -> take a rest, 1 -> visit
int bestChild[MAX_N][2];
ll ans = 0LL;
int root = -1;
bool isTaken = true;

// Stuff needed to retrieve the path

ll dp2[MAX_N];
int parity[MAX_N], from[MAX_N];

void dfs1(int v, int p) {
    ll sum = 0LL;
    ll bestNotTaken = 0LL;
    ll bestTaken = 0LL;
    bestChild[v][0] = bestChild[v][1] = -1;
    vector<PILL> taken, notTaken;

    for (int to: G[v]) {
        if (to == p) continue;
        sum += w[to];

        dfs1(to, v);

        // just update dp
        bestNotTaken = max(bestNotTaken, dp[to][0]);
        if (dp[to][1] - w[to] > bestTaken) {
            bestTaken = dp[to][1] - w[to];
        }

        taken.emplace_back(dp[to][1], to);
        notTaken.emplace_back(dp[to][0], to);
    }

    dp[v][0] = bestTaken + sum;
    dp[v][1] = bestNotTaken + w[v];

    // v is the lca of the path
    sort(taken.rbegin(), taken.rend());
    sort(notTaken.rbegin(), notTaken.rend());

    // set where answers come from
    if (!taken.empty()) {
        bestChild[v][0] = taken[0].second;
        bestChild[v][1] = notTaken[0].second;
    }

    // v is the lca of the path and we found a new best path
    // root is the highest node on such path
    // seperately consider cases where lca is taken or not
    if (taken.size() > 1) {
        ll tmp = taken[0].first + taken[1].first;
        if (p != -1) tmp += w[p];
        tmp += sum;
        tmp -= w[taken[0].second];
        tmp -= w[taken[1].second];
        if (tmp > ans) {
            ans = tmp;
            root = v;
            isTaken = false;
        }
    }

    if (notTaken.size() > 1) {
        ll tmp = notTaken[0].first + notTaken[1].first + w[v];
        if (tmp > ans) {
            ans = tmp;
            root = v;
            isTaken = true;
        }
    }
}

void setParity(int v, int p) {
    if (p == -1) {
        parity[v] = 1;
    } else {
        parity[v] = parity[p] ^ 1;
    }
    for (int to: G[v]) {
        if (to == p) continue;
        setParity(to, v);
    }
}

// brute force function to compute answer starting at the correct node
ll dfs2(int v, int p) {
    ll best = 0LL;
    int who = -1;
    ll sum = 0LL;

    for (int to: G[v]) {
        if (to == p) continue;
        sum += w[to];
        ll tmp = dfs2(to, v);
        if (tmp > best) {
            best = tmp;
            who = to;
        }
    }

    if (parity[v]) {
        dp2[v] = best;
    } else {
        dp2[v] = sum + best;
    }

    from[v] = who;
    return dp2[v];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(1, -1);

    if (root != -1) {   // if there is a 'lca' path
        // go down the tree to find the root - endpoint of the best path
        int now = root;
        while (now != -1) {
            if (isTaken) {
                root = now;
                now = bestChild[now][1];
            } else {
                now = bestChild[now][0];
            }
            isTaken ^= 1;
        }
    }

    if (dp[1][0] > ans) {
        ans = dp[1][0];
        root = bestChild[1][0];
    }
    if (dp[1][1] > ans) {
        ans = dp[1][1];
        root = 1;
    }

    cout << ans << "\n";

    // brute force approach to retrieve the answer

    setParity(root, -1);
    dfs2(root, -1);

    vector<int> res;
    int prv = -1;
    int now = root;

    while (true) {
        if (now == -1) break;
        res.push_back(now);
        if (!parity[now]) {
            for (int to: G[now]) {
                if (to == prv || to == from[now]) continue;
                res.push_back(to);
                res.push_back(now);
            }
        }
        prv = now;
        now = from[now];
    }

    if (!parity[res.back()]) res.pop_back();

    cout << (res.size() + 1) / 2 << "\n";
    for (int i: res) cout << i << " ";
    cout << "\n";

    return 0;
}