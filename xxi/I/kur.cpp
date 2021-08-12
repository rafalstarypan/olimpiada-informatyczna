#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - I Stage
    Problem name: Kurierzy
    Problem link: https://szkopul.edu.pl/problemset/problem/u14-MJgItr5hoHh2c0EBzDmS/site/?key=statement
*/

typedef pair<int, int> PII;
const int MAX_N = 5e5+5;

struct Query {
    int l;
    int r;
    int cand;
    int pos;
};

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

bool comp(Query q1, Query q2) {
    return q1.r < q2.r;
}

int getNextPow(int x) {
    int i = 0;
    while (pow(2, i) < x) i++;
    return pow(2, i);
}

int n, m;
int leaves;
int arr[MAX_N], ans[MAX_N], cnt[MAX_N];
PII t[4*MAX_N];             //krotnosc, wartosc
deque<Query> queries;
vector<int> wanted[MAX_N];
unordered_map<PII, int, hash_pair> mp;    //dla pary [l, cand] trzyma liczbe wystapien cand

void build() {
    for (int i=n; i>=1; i--) {       //liscie drzewa przedzialowego
        int v = i + leaves - 1;
        t[v] = {1, arr[i]};
    }

    for (int i=leaves-1; i>=1; i--) {     //wezly wewnetrzne drzewa przedzialowego
        int k1 = t[2*i].first;
        int w1 = t[2*i].second;
        int k2 = t[2*i+1].first;
        int w2 = t[2*i+1].second;
        if (w1 == w2) {
            t[i] = {k1+k2, w1};
        } else if (k1 - k2 > 0) {
            t[i] = {k1-k2, w1};
        } else {
            t[i] = {k2-k1, w2};
        }
    }
}

PII takeTogether(PII i, PII j) {
    PII ret;
    int k1 = i.first;
    int w1 = i.second;
    int k2 = j.first;
    int w2 = j.second;
    if (w1 == w2) {
        ret = {k1+k2, w1};
    } else if (k1 - k2 > 0) {
        ret = {k1-k2, w1};
    } else {
        ret = {k2-k1, w2};
    }
    return ret;
}

PII get(int left, int right) {
    int vL = left + leaves - 1;
    int vR = right + leaves - 1;
    PII resL = t[vL], resR = t[vR];

    while (vL/2 != vR/2) {
        if (vL%2 == 0) {
            resL = takeTogether(resL, t[vL+1]);
        }
        if (vR%2 == 1) {
            resR = takeTogether(resR, t[vR-1]);
        }
        vL /= 2;
        vR /= 2;
    }
    return takeTogether(resL, resR);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
    }
    leaves = getNextPow(n);

    build();

    for (int i=0; i<m; i++) {
        Query q;
        cin >> q.l >> q.r;
        q.pos = i;
        q.cand = get(q.l, q.r).second;
        queries.push_back(q);
        wanted[q.l-1].push_back(q.cand);
    }
    sort(queries.begin(), queries.end(), comp);

    int i = 0;
    bool ok = true;
    while (i <= n) {
        if (ok) cnt[arr[i]]++;
        if (!wanted[i].empty()) {
            for (auto x: wanted[i]) {
                mp[{i, x}] = cnt[x];
            }
        }
        if (!queries.empty() && i == queries.front().r) {
            int r = i;
            int l = queries.front().l-1;
            int c = queries.front().cand;
            int pos = queries.front().pos;
            if (cnt[c] - mp[{l,c}] > (r-l)/2) {
                ans[pos] = c;
            } else {
                ans[pos] = 0;
            }
            queries.pop_front();
            ok = false;
        } else {
            i++;
            ok = true;
        }
    }

    for (int i=0; i<m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
