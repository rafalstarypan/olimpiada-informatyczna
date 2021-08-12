#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXI OI - II Stage
    Problem name: Karty
    Problem link: https://szkopul.edu.pl/problemset/problem/EHW4BOJee7VD-R9MaDAokZ6O/site/?key=statement
*/

typedef pair<int, int> PII;

const int MAX_N = 2e5+5;
const int inf = 1e9;

struct Node {
    bool x1_x2;
    bool x1_y2;
    bool y1_x2;
    bool y1_y2;
    int l;
    int r;
};

int n, Q;
PII arr[MAX_N];

Node t[4*MAX_N];

Node pull(Node a, Node b) {
    Node newNode;
    newNode.l = a.l;
    newNode.r = b.r;

    bool n_x1_x2 = false;
    bool n_x1_y2 = false;
    bool n_y1_x2 = false;
    bool n_y1_y2 = false;

    // n_x1_x2

    if (a.x1_x2 && b.x1_x2 && arr[a.r].first <= arr[b.l].first) {
        n_x1_x2 = true;
    }
    if (a.x1_x2 && b.y1_x2 && arr[a.r].first <= arr[b.l].second) {
        n_x1_x2 = true;
    }
    if (a.x1_y2 && b.x1_x2 && arr[a.r].second <= arr[b.l].first) {
        n_x1_x2 = true;
    }
    if (a.x1_y2 && b.y1_x2 && arr[a.r].second <= arr[b.l].second) {
        n_x1_x2 = true;
    }

    // n_x1_y2

    if (a.x1_x2 && b.x1_y2 && arr[a.r].first <= arr[b.l].first) {
        n_x1_y2 = true;
    }
    if (a.x1_x2 && b.y1_y2 && arr[a.r].first <= arr[b.l].second) {
        n_x1_y2 = true;
    }
    if (a.x1_y2 && b.x1_y2 && arr[a.r].second <= arr[b.l].first) {
        n_x1_y2 = true;
    }
    if (a.x1_y2 && b.y1_y2 && arr[a.r].second <= arr[b.l].second) {
        n_x1_y2 = true;
    }

    // n_y1_x2

    if (a.y1_x2 && b.x1_x2 && arr[a.r].first <= arr[b.l].first) {
        n_y1_x2 = true;
    }
    if (a.y1_x2 && b.y1_x2 && arr[a.r].first <= arr[b.l].second) {
        n_y1_x2 = true;
    }
    if (a.y1_y2 && b.x1_x2 && arr[a.r].second <= arr[b.l].first) {
        n_y1_x2 = true;
    }
    if (a.y1_y2 && b.y1_x2 && arr[a.r].second <= arr[b.l].second) {
        n_y1_x2 = true;
    }

    // n_y1_y2

    if (a.y1_x2 && b.x1_y2 && arr[a.r].first <= arr[b.l].first) {
        n_y1_y2 = true;
    }
    if (a.y1_x2 && b.y1_y2 && arr[a.r].first <= arr[b.l].second) {
        n_y1_y2 = true;
    }
    if (a.y1_y2 && b.x1_y2 && arr[a.r].second <= arr[b.l].first) {
        n_y1_y2 = true;
    }
    if (a.y1_y2 && b.y1_y2 && arr[a.r].second <= arr[b.l].second) {
        n_y1_y2 = true;
    }

    newNode.x1_x2 = n_x1_x2;
    newNode.x1_y2 = n_x1_y2;
    newNode.y1_x2 = n_y1_x2;
    newNode.y1_y2 = n_y1_y2;

    return newNode;
}

void build(int v, int l, int r) {
    if (l == r) {
        bool y1_x2 = arr[l].second <= arr[l].first;
        Node leaf = {true, false, false, true, l, r};
        t[v] = leaf;
        return;
    }
    int mid = (l+r) / 2;
    build(2*v, l, mid);
    build(2*v+1, mid+1, r);

    t[v] = pull(t[2*v], t[2*v+1]);
}

void update(int v, int l, int r, int pos) {
    if (l == pos && r == pos) {
        return;
    }
    if (l > pos || r < pos) return;

    int mid = (l+r) / 2;
    update(2*v, l, mid, pos);
    update(2*v+1, mid+1, r, pos);

    t[v] = pull(t[2*v], t[2*v+1]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> arr[i].first >> arr[i].second;
		if (arr[i].first > arr[i].second) {
			swap(arr[i].first, arr[i].second);
		}
	}
	arr[0] = {-1, -1};
	arr[n+1] = {inf, inf};

	build(1, 1, n);

    cin >> Q;
	for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        swap(arr[l], arr[r]);
        update(1, 1, n, l);
        update(1, 1, n, r);
        if (t[1].x1_x2 || t[1].x1_y2 || t[1].y1_x2 || t[1].y1_y2) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
	}




	return 0;
}
