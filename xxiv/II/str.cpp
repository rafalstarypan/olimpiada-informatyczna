#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - II Stage
    Problem name: Strajki
    Problem link: https://szkopul.edu.pl/problemset/problem/lR_LabSUC2n7EMmDHpw-wk_b/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<int, ll> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 5e5+5;
const int M = 1e6;
const ll INF = (ll)(1e18);
const int inf = 1e9;
const ll MOD = 1000000007LL;
const int HEAVY = 50;

int n, Q;
bool blocked[MAX_N], vis[MAX_N];
vector<int> G[MAX_N];
set<int> matrix[MAX_N];
vector<int> queries;
vector<int> heavy;
int activeCnt[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        matrix[u].insert(v);
        matrix[v].insert(u);
    }

    bool onlyPositive = true;
    cin >> Q;
    queries.resize(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i];
        if (queries[i] < 0) {
            onlyPositive = false;
        }
    }

    int ones = 0;
    int twos = 0;
    for (int i = 1; i <= n; i++) {
        if (G[i].size() == 1) ones++;
        if (G[i].size() == 2) twos++;
        if (G[i].size() > HEAVY) heavy.push_back(i);
        activeCnt[i] = (int)G[i].size();
    }

    int ans = 1;
    for (int i = 0; i < Q; i++) {
        int z = queries[i];
        if (z > 0) {
            int active = 0;
            if (G[z].size() > HEAVY) {
                active = activeCnt[z];
                for (auto h: heavy) {
                    if (matrix[z].count(h)) activeCnt[h]--;
                }
            } else {
                for (auto to: G[z]) {
                    if (!blocked[to]) active++;
                    activeCnt[to]--;
                }
            }
            if (active == 0) ans--;
            else ans += active-1;
            blocked[z] = true;
        } else {
            z = abs(z);
            int active = 0;
            if (G[z].size() > HEAVY) {
                active = activeCnt[z];
                for (auto h: heavy) {
                    if (matrix[z].count(h)) activeCnt[h]++;
                }
            } else {
                for (auto to: G[z]) {
                    if (!blocked[to]) active++;
                    activeCnt[to]++;
                }
            }
            if (active == 0) ans++;
            else ans -= active-1;
            blocked[z] = false;
        }

        cout << ans << "\n";
    }


    return 0;
}
