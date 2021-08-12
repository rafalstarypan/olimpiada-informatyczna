#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXVII OI - I stage 
    Problem name: Pisarze
    Problem link: https://szkopul.edu.pl/problemset/problem/v2Y2_UW56ENMcbwP22tkTb7a/site/?key=statement

    This solution scores 72 points.
*/ 


#define p push_back

const string M = "Mickiewicz";
const string P = "Prus";
const string S = "Sienkiewicz";

vector<string> t, tS, q, qS, l, lS;
string s;

bool isAlphaNum(char c) {
    return (c >= 'a' && c <='z') || (c >='A' && c <= 'Z') || (c >= '0' && c <= '9');
}

char asclow(char c) {
    if (c <= 'Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}

bool compStr(string str, string pat, bool flag) {
    int n = (int)str.size();
    int m = (int)pat.size();
    if (abs(n-m) > 3) return false;
    if (flag) {
        transform(str.begin(), str.end(), str.begin(), asclow);
        transform(pat.begin(), pat.end(), pat.begin(), asclow);
    }
    return (str.find(pat) != string::npos);
}

string solve() {
    getline(cin, s);
    vector<string> a;
    deque<string> rym;
    string cur; cur.clear();
    int n = (int)s.size();
    bool digit = false, star = false;

    for (int i=0; i<n; i++) {
        if (s[i] == '*') {
            star = true;
        }
        if (s[i] >= '0' && s[i] <= '9') {
            digit = true;
        }
        if (isAlphaNum(s[i])) {
            cur += s[i];
        } else if (s[i] == ' ') {
            a.p(cur);
            cur.clear();
        }
    }
    a.p(cur);

    if (star) {
        return M;
    }
    if (digit) {
        return P;
    }

    int totRym = 0;
    int tadek = 0, vadis = 0, lalka = 0;
    for (int i=0; i<a.size(); i++) {
        string x = a[i];
        int m = (int)x.size();
        if (m > 3) {
            string tmp = x.substr(m-3, 3);
            if (rym.size() < 4) {
                rym.push_back(tmp);
            } else {
                if (rym.size() > 6) {
                    rym.pop_front();
                }
                for (int j=0; j<rym.size()-3; j++) {
                    if (rym[j] == tmp) totRym++;
                }
                rym.push_back(tmp);
            }
        }
        for (int j=0; j<t.size(); j++) {
            if (compStr(x, t[j], false)) {
                tadek++;
            }
        }
        for (int j=0; j<q.size(); j++) {
            if (compStr(x, q[j], false)) {
                vadis++;
            }
        }
        for (int j=0; j<l.size(); j++) {
            if (compStr(x, l[j], false)) {
                lalka++;
            }
        }
        for (int j=0; j<qS.size(); j++) {
            if (compStr(x, qS[j], true)) {
                vadis++;
            }
        }
        for (int j=0; j<lS.size(); j++) {
            if (compStr(x, lS[j], true)) {
                lalka++;
            }
        }
    }

    if (tadek > vadis && tadek > lalka) {
        return M;
    }
    if (vadis > tadek && vadis > lalka) {
        return S;
    }
    if (lalka > tadek && lalka > vadis) {
        return P;
    }

    if (a.size() < 41 && totRym > 0) {
        return M;
    }
    if (a.size() < 61 && totRym > 1) {
        return M;
    }
    if (a.size() < 101 && totRym > 2) {
        return M;
    }
    if (a.size() > 100 && totRym*25 >= a.size()) {
        return M;
    }
    return S;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    t.p("Tadeusz");
    t.p("Gerwaz");
    t.p("Telimen");
    t.p("Sopl");
    t.p("Robak");
    t.p("Wojski");
    t.p("Zosi");
    t.p("Horeszko");
    t.p("Maciej");
    t.p("Rykow");
    t.p("Bernardyn");
    t.p("Asesor");
    t.p("Dabrowski");
    t.p("Jankiel");
    t.p("Dobrzyn");
    t.p("Litw");
    t.p("Jacek");
    t.p("Stolnik");
    t.p("Podkomorzy");
    t.p("Sedzia");
    t.p("Podkomorz");

    q.p("Petroniusz");
    q.p("Winicjusz");
    q.p("Ligi");
    q.p("Chilo");
    q.p("Nero");
    q.p("Akte");
    q.p("Eunic");
    q.p("Tygellin");
    q.p("Glauk");
    q.p("Poppe");
    q.p("Pomponi");
    q.p("Piotr");
    q.p("Pawel");
    q.p("Pawla");
    q.p("Aulus");
    q.p("August");
    q.p("Rzym");
    q.p("Ursus");
    q.p("Chrystus");
    q.p("Senek");
    q.p("Grek");
    q.p("Zatyb");
    q.p("Kroto");
    q.p("Palaty");
    q.p("Jowisz");
    q.p("Zeus");
    qS.p("niewolni");
    qS.p("chrzescijan");
    qS.p("bogow");
    qS.p("bogin");
    qS.p("pretorian");
    qS.p("cezar");
    qS.p("rzymski");
    qS.p("patrycjusz");
    qS.p("carissim");

    l.p("Wokulski");
    l.p("Rzecki");
    l.p("Lecki");
    l.p("Lecka");
    l.p("Izabela");
    l.p("Tomasz");
    l.p("Zaslawska");
    l.p("Wasowsk");
    l.p("Starski");
    l.p("Ochocki");
    l.p("Krzeszowski");
    l.p("Deklewski");
    l.p("Krzeszows");
    l.p("Misiewicz");
    l.p("Stawsk");
    l.p("Ignac");
    l.p("Mraczewski");
    l.p("Lisiecki");
    l.p("Klejn");
    l.p("Zieb");
    l.p("Szlangbaum");
    l.p("Szuman");
    l.p("Geist");
    l.p("Szprot");
    l.p("Meliton");
    l.p("Wegrowicz");
    l.p("Stach");
    l.p("Zyd");
    l.p("Warszaw");
    l.p("Mincel");
    lS.p("sklep");
    lS.p("kamienic");
    lS.p("pociag");
    lS.p("weksl");
    lS.p("bank");
    lS.p("bankier");
    lS.p("rubl");
    lS.p("spolk");
    lS.p("prezes");
    lS.p("subiekt");
    lS.p("pan");

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    for(int i = 0; i < T; i++) {
        cout << solve() << "\n";
    }

    return 0;
}