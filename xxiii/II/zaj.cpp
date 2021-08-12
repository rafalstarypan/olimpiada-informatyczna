#include <bits/stdc++.h>
using namespace std;

/*
    Author: Rafal Starypan
    Contest: XXIII OI - II Stage
    Problem name: Zajakniecia
    Problem link: https://szkopul.edu.pl/problemset/problem/Orc2Z7ti1xLaUUQDT1a6RGR5/site/?key=statement
*/

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef pair<ll, int> PILL;
typedef pair<ll, ll> PLL;

const int MAX_N = 1e5+5;
const ll MOD = (ll)(1e9+7);
const ll INF = (ll) (1e18);
const int inf = 1e9;

int n, m;
int A[15005], B[15005], memo[15005], prevA[15005], prevB[15005];
int dp[2][15005];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> A[i];
    }
    for (int i=1; i<=m; i++) {
        cin >> B[i];
    }

    for (int i=1; i<=n; i++) {
        for (int j=i-1; j>=1; j--) {
            if (A[i] == A[j]) {
                prevA[i] = j;
                break;
            }
        }
    }
    for (int i=1; i<=m; i++) {
        for (int j=i-1; j>=1; j--) {
            if (B[i] == B[j]) {
                prevB[i] = j;
                break;
            }
        }
    }

    for (int i=1; i<=m; i++) {
        dp[0][i] = memo[i] = 0;
    }

    for (int i=1; i<=n; i++) {
        dp[i%2][0] = 0;
        for (int j=1; j<=m; j++) {
            if (A[i] == B[j] && prevA[i] > 0 && prevB[j] > 0) {
                dp[i%2][j] = memo[prevB[j]] + 2;
            } else {
                dp[i%2][j] = 0;
            }
            dp[i%2][j] = max(dp[i%2][j], dp[(i-1)%2][j]);
            dp[i%2][j] = max(dp[i%2][j], dp[i%2][j-1]);
        }
        for (int j=1; j<=m; j++) {
            if (A[i] == B[j]) memo[j] = dp[(i-1)%2][j-1];
        }
    }

    cout << dp[n%2][m];

    return 0;
}
