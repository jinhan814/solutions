#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector adj(n + 1, vector(0, 0));
	vector c(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		c[x] = 1;
	}
	vector dp(n + 1, vector(k + 1, 1));
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			for (int i = k; i >= 0; i--) {
				for (int j = 0; j <= i; j++)
					dp[cur][i] = max(dp[cur][i], dp[cur][i - j] + dp[nxt][j]);
			}
		}
		if (c[cur]) {
			for (int i = k; i >= 1; i--) dp[cur][i] = dp[cur][i - 1];
			dp[cur][0] = 0;
		}
	};
	dfs(dfs, 1, 0);
	cout << dp[1][k] << '\n';
}