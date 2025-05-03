#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	vector dp(n + 1, vector(n, 1LL << 60)); dp[1][0] = 0;
	for (int t = 1; t < n; t++) {
		for (int i = 1; i <= n; i++)
			for (auto [j, cost] : adj[i])
				dp[i][t] = min(dp[i][t], dp[j][t - 1] + cost);
	}

	vector hull(0, 0);
	for (int t = n - 1; t >= 0; t--) {
		if (dp[n][t] >> 60) continue;
		while (hull.size() >= 2) {
			i64 a1 = hull.end()[-2], a0 = dp[n][a1];
			i64 b1 = hull.back(), b0 = dp[n][b1];
			i64 c1 = t, c0 = dp[n][t];
			if ((a1 - c1) * (b0 - a0) <= (a1 - b1) * (c0 - a0)) break;
			hull.pop_back();
		}
		hull.push_back(t);
	}
	reverse(hull.begin(), hull.end());
	while (hull.size() >= 2) {
		i64 a1 = hull.back(), a0 = dp[n][a1];
		i64 b1 = hull.end()[-2], b0 = dp[n][b1];
		if (a0 <= b0) break;
		hull.pop_back();
	}

	vector c(n + 1, vector(n, 0));
	vector q(0, pair(0, 0));
	for (int t : hull) c[n][t] = 1, q.push_back({ n, t });
	while (q.size()) {
		auto [i, t] = q.back(); q.pop_back();
		if (t == 0) continue;
		for (auto [j, cost] : adj[i]) {
			if (dp[j][t - 1] + cost != dp[i][t]) continue;
			if (c[j][t - 1]) continue;
			c[j][t - 1] = 1, q.push_back({ j, t - 1 });
		}
	}

	vector res(0, 0);
	for (int i = 1; i <= n; i++) {
		if (reduce(c[i].begin(), c[i].end())) continue;
		res.push_back(i);
	}
	cout << res.size() << '\n';
	for (int i : res) cout << i << ' ';
	cout << '\n';
}