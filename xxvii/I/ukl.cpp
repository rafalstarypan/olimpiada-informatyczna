#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

/*
    Author: Rafal Starypan
    Contest: XXVII OI - I stage 
    Problem: Uklad scalony
    Problem link: https://szkopul.edu.pl/problemset/problem/Pc6EAN80QSM9M34nmz_RtjtI/site/?key=statement
*/

struct Bolec {
    PII e;
    int pos;
};

int n, m, k;
int mini, maxi;
vector<PII> res;

int cellToNumber(int x, int y) {
    return (x-1)*m + y;
}

PII numberToCell(int num) {
    int y = num % m;
    if (y == 0) y = m;
    num -= y;
    int x = num / m + 1;
    return {x, y};
}

void print(vector<PII> v) {
    for (PII p: v) {
        int u = p.first;
        int v = p.second;
        PII a = numberToCell(u);
        PII b = numberToCell(v);
        cout << a.first << " " << a.second << " " << b.first << " " << b.second << "\n";
    }
}

void solveN1() {
    vector<PII> ans;
    for (int i=1; i<m; i++) {
        ans.push_back({i, i+1});
    }
    cout << "TAK\n";
    print(ans);
}

void solveM1() {
    vector<PII> ans;
    for (int i=1; i<n; i++) {
        ans.push_back({i, i+1});
    }
    cout << "TAK\n";
    print(ans);
}

vector<PII> solveN2() {
    int cur = n*m - 1;
    set<PII> st;
    for (int i=1; i<m; i++) {
        st.insert({i, i+1});
    }
    st.insert({m, 2*m});
    for (int i=m+1; i<2*m; i++) {
        st.insert({i, i+1});
    }

    if (k%2 != cur%2) {
        st.erase({1, 2});
        st.erase({2, 3});
        st.insert({1, m+1});
        st.insert({2, m+2});
        cur--;
    }

    PII curPair = {m, 2*m};
    while (cur > k) {
        int x = curPair.first - 1;
        int y = curPair.second - 1;
        st.erase(curPair);
        curPair = {x, y};
        st.insert(curPair);
        cur -= 2;
    }

    vector<PII> ans; for (PII p: st) ans.push_back(p);
    return ans;
}

vector<PII> solveM2() {
    int cur = n*m - 1;
    set<PII> st;
    for (int i=1; i<2*n-1; i+=2) {
        st.insert({i, i+2});
    }
    st.insert({2*n-1, 2*n});
    for (int i=2; i<2*n; i+=2) {
        st.insert({i, i+2});
    }

    if (k%2 != cur%2) {
        st.erase({1, 3});
        st.erase({3, 5});
        st.insert({1, 2});
        st.insert({3, 4});
        cur--;
    }

    PII curPair = {2*n-1, 2*n};
    while (cur > k) {
        int x = curPair.first - 2;
        int y = curPair.second - 2;
        st.erase(curPair);
        curPair = {x, y};
        st.insert(curPair);
        cur -= 2;
    }

    vector<PII> ans; for (PII p: st) ans.push_back(p);
    return ans;
}

vector<PII> solve() {
    int cur = n*m - 1;
    int mid = m / 2 + 1;
    vector<PII> ans;
    deque<Bolec> bolce;

    for (int i=1; i<n*m; i++) {
        if (i%m == 0) continue;
        ans.push_back({i, i+1});
    }

    for (int i = m; ; i += 2*m) {
        if (i+m > n*m) break;
        PII p = {i, i+m};
        bolce.push_back({p, m});
        if (i+m+1 > n*m) break;
        p = {i+1, i+1+m};
        bolce.push_back({p, 1});
    }

    while (cur > k) {
        int pos = bolce.front().pos;
        PII p = bolce.front().e;
        while (pos != mid && cur > k) {
            int x = p.first;
            int y = p.second;
            if (mid < pos) {
                pos--;
                p = {x-1, y-1};
            } else {
                pos++;
                p = {x+1, y+1};
            }
            cur -= 2;
        }
        ans.push_back(p);
        bolce.pop_front();
    }

    for (int i = 0; i < bolce.size(); i++) {
        ans.push_back(bolce[i].e);
    }
    return ans;
}

vector<PII> solveReduced() {
    int cur = n*m - 2;
    int mid = ((m+1) / 2) + 1;
    vector<PII> ans;
    deque<Bolec> bolce;

    ans.push_back({1, m+1});
    for (int i = 2; i < n*m; i++) {
        if (i%m == 0) continue;
        ans.push_back({i, i+1});
    }

    for (int i = m; ; i += 2*m) {
        if (i+m > n*m) break;
        PII p = {i, i+m};
        bolce.push_back({p, m});
        if (i+m+1 > n*m) break;
        p = {i+1, i+1+m};
        bolce.push_back({p, 1});
    }

    int pos = bolce[0].pos;
    PII p = bolce[0].e;
    while (cur > k && pos != mid) {
        int x = p.first;
        int y = p.second;
        p = {x-1, y-1};
        pos--;
        cur -= 2;
    }
    ans.push_back(p);
    bolce.pop_front();
    mid = (m+1) / 2;

    if (cur == k) {
        for (int i = 0; i < bolce.size(); i++) {
            ans.push_back(bolce[i].e);
        }
        return ans;
    }

    while (cur > k) {
        int pos = bolce.front().pos;
        PII p = bolce.front().e;
        while (pos != mid && cur > k) {
            int x = p.first;
            int y = p.second;
            if (mid < pos) {
                pos--;
                p = {x-1, y-1};
            } else {
                pos++;
                p = {x+1, y+1};
            }
            cur -= 2;
        }
        ans.push_back(p);
        bolce.pop_front();
    }
    for (int i = 0; i < bolce.size(); i++) {
        ans.push_back(bolce[i].e);
    }
    return ans;
}

vector<PII> specialCase() {
    vector<PII> ans;
    int mid = (n / 2) + 1;
    int midStart = (mid-1)*m + 1;
    for (int i = midStart; i+1 < midStart + m; i++) {
        ans.push_back({i, i+1});
    }

    for (int i = 1; i <= m; i++) {
        for (int j = i; j+m <= n*m; j += m) {
            ans.push_back({j, j+m});
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    if (n == 1 && m == 1) {
        if (k == 0) {
            cout << "TAK";
        } else {
            cout << "NIE";
        }
        return 0;
    }

    if (n == 1) {
        if (k != m-1) {
            cout << "NIE";
        } else {
            solveN1();
        }
        return 0;
    }

    if (m == 1) {
        if (k != n-1) {
            cout << "NIE";
        } else {
            solveM1();
        }
        return 0;
    }

    maxi = n*m - 1;
    if (n%2 || m%2) {
        mini = n+m-2;
    } else {
        mini = n+m-1;
    }

    if (k > maxi || k < mini) {
        cout << "NIE";
        return 0;
    }
    cout << "TAK\n";

    if (n == 2) {
        res = solveN2();
        print(res);
        return 0;
    }

    if (m == 2) {
        res = solveM2();
        print(res);
        return 0;
    }

    if (n%2 == 1 && m%2 == 0 && k == mini) {
        res = specialCase();
        print(res);
        return 0;
    }

    if (maxi%2 == k%2) {
        res = solve();
    } else {
        res = solveReduced();
    }
    print(res);




    return 0;
}