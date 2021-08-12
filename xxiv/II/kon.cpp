#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIV OI - II Stage
    Problem name: Kontenery
    Problem link: https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/site/?key=statement
*/

typedef pair<int, int> PII;
typedef long long ll;

const int MAX_N = 1e5+5;
const int M = 1e6+5;
const int inf = 1e9;

int n, k;
int a[MAX_N], l[MAX_N], d[MAX_N];
int big[MAX_N];
int small[325][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		cin >> a[i] >> l[i] >> d[i];
	}
	
	const int SQRT = (int)sqrt(n);
	
	for (int i = 0; i < k; i++) {
		if (d[i] >= SQRT) {
			int pos = a[i];
			for (int j = 0; j < l[i]; j++) {
				big[pos]++;
				pos += d[i];
			}
			continue;
		}
		
		int row = d[i];
		int start = a[i];
		int stop = a[i] + l[i] * d[i];
		small[row][start]++;
		if (stop <= n) small[row][stop]--;
	}
	
	for (int i = 1; i <= n; i++) {
		int res = big[i];
		for (int j = 1; j < SQRT; j++) {
			if (i-j < 1) {
				res += small[j][i];
				continue;
			}
			small[j][i] += small[j][i-j];
			res += small[j][i];
		}
		res = max(res, 0);
		cout << res << " ";
	}
	cout << '\n';
  

    return 0;
}
