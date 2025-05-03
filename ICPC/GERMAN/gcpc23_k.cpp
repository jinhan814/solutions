#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector p(m + 1, n);
	for (int i = 0; i < m; i++) cin >> p[i];
	for (int i = 1; i < m; i++) p[i] += p[i - 1];

	vector f(n + 1, 1);
	for (int i = 1; i <= n; i++) f[i] = 1LL * f[i - 1] * i % mod;

	vector dp(m + 1, 0);
	for (int i = 0; i <= m; i++) {
		dp[i] = f[p[i]];
		for (int j = 0; j < i; j++) {
			dp[i] -= 1LL * dp[j] * f[p[i] - p[j]] % mod;
			if (dp[i] < 0) dp[i] += mod;
		}
	}
	cout << (m && p[m - 1] == n ? 0 : dp[m]) << '\n';
}