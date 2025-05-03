#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector dp(n + 1, 1LL << 60); dp[0] = 0;
	for (int i = 0; i < n; i++) {
		int c; cin >> c; dp[i] += c;
		for (int j = 1; j <= min(m, n - i); j++) {
			int x; cin >> x;
			dp[i + j] = min(dp[i + j], dp[i] - x);
		}
	}
	cout << dp[n] << '\n';
}