#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	int m; cin >> m;
	vector data(m, pair(0, vector(0, string{})));
	for (auto& [x, buc] : data) {
		int k; cin >> k >> x;
		buc.resize(k);
		for (string& s : buc) cin >> s;
	}

	sort(v.begin(), v.end());
	auto get_idx = [&](string s) {
		auto it = lower_bound(v.begin(), v.end(), s);
		return it - v.begin() + 1;
	};

	vector g(n + 1, vector(n + 1, 1));
	vector dp(n + 1, 0);
	for (auto& [x, buc] : data) {
		vector c(n + 1, 0);
		for (string s : buc) c[get_idx(s)] = 1;
		for (int i = 1; i <= n; i++) {
			if (c[i]) dp[i] = max(dp[i], x);
			else g[i][x] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < dp[i]; j++)
			g[i][j] = 0;
	}

	vector par(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		vector c(n + 1, 0);
		auto dfs = [&](const auto& self, int cur) -> bool {
			if (c[cur]) return 0;
			c[cur] = 1;
			for (int nxt = 1; nxt <= n; nxt++) {
				if (!g[cur][nxt]) continue;
				if (par[nxt] && !self(self, par[nxt])) continue;
				par[nxt] = cur;
				return 1;
			}
			return 0;
		};
		dfs(dfs, i);
	}
	for (int i = 1; i <= n; i++) cout << v[par[i] - 1] << ' ';
	cout << '\n';
}