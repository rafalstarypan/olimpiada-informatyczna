#include <bits/stdc++.h>
using namespace std;

/*
	Author: Rafal Starypan
	Contest: XXVI OI - II stage
	Problem name: Rozliczenia
	Problem link: https://szkopul.edu.pl/problemset/problem/7feyJYY7uz_g6iGLS_QPwJVG/site/?key=statement
*/

int n;
int curPos = 0;
int totalSize = 0;
vector<long long> fen;

long long query(int pos) {
    long long ret = 0LL;
    while (pos > 0) {
        ret += fen[pos];
        int lsb = pos & (-pos);
        pos -= lsb;
    }
    return ret;
}

long long getSum(int l, int r) {
    l--;
    return query(r) - query(l);
}

void update(int pos, long long val) {
    while (pos <= n) {
        fen[pos] += val;
        int lsb = pos & (-pos);
        pos += lsb;
    }
}

void inicjuj(int m) {
    n = m;
    fen.resize(m+1);
}

void dodaj(int k) {
    long long kAsLL = (long long)k;
    curPos++;
    totalSize++;
    if (curPos > n) {
        curPos = 1;
    }
    long long curVal = getSum(curPos, curPos);
    kAsLL = k - curVal;
    update(curPos, kAsLL);
}

void koryguj(int i, int k) {
    long long kAsLL = (long long)k;
    i--;
    if (curPos - i >= 1) {
        update(curPos - i, kAsLL);
        return;
    }
    i = i - curPos;
    i = n - i;
    update(i, kAsLL);
}

long long suma(int i) {
    if (totalSize <= n) {
        i = max(1, curPos - i + 1);
        return getSum(i, curPos);
    }

    int tmp = max(1, curPos - i + 1);
    long long a = getSum(tmp, curPos);
    i -= curPos;
    if (i <= 0) {
        return a;
    }

    long long b = getSum(n-i+1, n);
    return a+b;
}

/*int main() {
    inicjuj(3);
    dodaj(-6);
    cout << suma(1) << "\n";
    dodaj(5);
    koryguj(2, 10);
    cout << "D: " << fen[1] << "\n";
    cout << suma(3) << "\n";
    cout << suma(1) << "\n";
    dodaj(5);
    cout << suma(1) << "\n";
    cout << suma(2) << "\n";
    cout << suma(3) << "\n";
    dodaj(20);
    cout << suma(1) << "\n";
    cout << suma(2) << "\n";
    cout << suma(3) << "\n";

}*/










