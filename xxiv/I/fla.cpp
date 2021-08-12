#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - I Stage
    Problem name: Flappy Bird
    Problem link: https://szkopul.edu.pl/problemset/problem/eLy9p2a1VStZ4y9y-LdeB-8f/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e6+5;
const int MAX_K = 2e6+5;

bool checkRange(PII p, int x) {
    int lowest = p.first;
    int highest = p.second;
    int index;
    for (int index=lowest; index<=highest; index++) {
        int tmp = abs(index);
        if (tmp%2 == x%2) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, X;
    int x, ai, bi;
    int previousObstacle = 0, dist;
    PII range = {0, 0};

    cin >> n >> X;
    if (n == 0) {
        cout << 0;
        return 0;
    }

    for (int i=0; i<n; i++) {
        cin >> x >> ai >> bi;
        ai++; bi--;
        if (abs(x)%2 != abs(ai)%2) ai++;
        if (abs(x)%2 != abs(bi)%2) bi--;
        dist = x - previousObstacle;
        int tmp1 = range.first - dist;
        int tmp2 = range.second + dist;
        range.first = max(tmp1, ai);
        range.second = min(tmp2, bi);
        if (abs(x)%2 != abs(range.first)%2) {
        	return 0;
        }
        if (!checkRange(range, x)) {
            cout << "NIE";
            return 0;
        }
        previousObstacle = x;
    }

    int lowest = range.first;
    int highest = range.second;
    int finalPoint;

    int index;
    for (index=lowest; index<=highest; index++) {
        int tmp = abs(index);
        if (tmp%2 == previousObstacle%2) {
            finalPoint = index;
            break;
        }
    }

    if (index > highest) {
        cout << "NIE";
        return 0;
    }
    cout << (previousObstacle + finalPoint) / 2;
    return 0;
}
