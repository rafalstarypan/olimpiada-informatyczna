#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIII OI - II Stage
    Problem name: Drogi zmiennokierunkowe
    Problem link: https://szkopul.edu.pl/problemset/problem/9TaxfuNdAv2FPpQ6PeB-vlti/site/?key=statement
*/

const int MAX_N = 1e6+5;

int n, m;
int whichScc[MAX_N];
vector<int> G[MAX_N], revG[MAX_N], sccList[MAX_N];
vector<int> rFunction;
vector<int> st;
bool visited[MAX_N], bad[MAX_N];
int scc, ans;

void visReset() {
    for (int i=1; i<=n; i++) {
       visited[i] = false;
    }
}

void reset() {
    for (int i=1; i<scc; i++) {
        rFunction[i] = 0;
    }
}

void dfs1(int v) {
    visited[v] = true;
    for (auto adj: G[v]) {
        if (!visited[adj]) {
            dfs1(adj);
        }
    }
    st.push_back(v);
}

void dfs2(int v, int scc) {
    visited[v] = true;
    whichScc[v] = scc;
    sccList[scc].push_back(v);
    for (auto adj: revG[v]) {
        if (!visited[adj]) {
            dfs2(adj, scc);
        }
    }
}

void findBad() {
    for (int i=1; i<scc; i++) {
        for (auto x: sccList[i]) {
            for (auto y: G[x]) {
                int tmp = whichScc[y];
                if (tmp != i) {
                    rFunction[i] = min(rFunction[i], tmp);
                }
            }
        }
    }

    int cur = rFunction[1];
    for (int i=2; i<scc; i++) {
        if (cur > i) {
            for (auto x: sccList[i]) {
                if (!bad[x]) {
                    bad[x] = true;
                    ans--;
                }
            }
        }
        cur = max(cur, rFunction[i]);
    }
}

void findBad2() {
    for (int i=scc-1; i>=1; i--) {
        for (auto x: sccList[i]) {
            for (auto y: revG[x]) {
                int tmp = whichScc[y];
                if (tmp != i) {
                    rFunction[i] = max(rFunction[i], tmp);
                }
            }
        }
    }

    int cur = rFunction[scc-1];
    for (int i=scc-2; i>=1; i--) {
        if (cur < i) {
            for (auto x: sccList[i]) {
                if (!bad[x]) {
                    bad[x] = true;
                    ans--;
                }
            }
        }
        cur = min(cur, rFunction[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    ans = n;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        revG[v].push_back(u);
    }

    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    visReset();

    scc = 1;
    for (int i=n-1; i>=0; i--) {
        int v = st[i];
        if (!visited[v]) {
            dfs2(v, scc);
            scc++;
        }
    }

    rFunction.resize(scc);
    for (int i=1; i<scc; i++) {
        rFunction[i] = n+1;
    }

    findBad();

    reset();

    findBad2();

    cout << ans << "\n";
    for (int i=1; i<=n; i++) {
        if (!bad[i]) cout << i << " ";
    }


    return 0;
}
