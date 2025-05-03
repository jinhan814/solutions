#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	vector d1(n + 1, 1 << 30);
	set pq{ pair(d1[1] = 0, 1) };
	while (pq.size()) {
		auto [cdist, cur] = *pq.begin(); pq.erase(pq.begin());
		for (auto [nxt, cost] : adj[cur]) {
			if (d1[nxt] <= cdist + cost) continue;
			pq.erase({ d1[nxt], nxt });
			pq.insert({ d1[nxt] = cdist + cost, nxt });
		}
	}

	vector dp(n + 1, -1);
	auto dfs = [&](const auto& self, int cur) -> int {
		if (cur == n) return 1;
		int& ret = dp[cur];
		if (ret != -1) return ret; ret = 0;
		for (auto [nxt, cost] : adj[cur]) {
			if (d1[nxt] != d1[cur] + cost) continue;
			dp[cur] += self(self, nxt);
			if (dp[cur] > 1) dp[cur] = 2;
		}
		return ret;
	};

	if (dfs(dfs, 1) == 0) return cout << -1 << '\n', 0;
	if (dfs(dfs, 1) == 2) return cout << 2 * d1[n] << '\n', 0;

	vector d2(n + 1, array{ 1 << 30, 1 << 30 });
	set pq2{ tuple(d2[1][0] = 0, 1, 0) };
	while (pq2.size()) {
		auto [cdist, cur, s] = *pq2.begin(); pq2.erase(pq2.begin());
		for (auto [nxt, cost] : adj[cur]) {
			auto ns = s || !dfs(dfs, nxt) || (abs(d1[nxt] - d1[cur]) != cost);
			if (d2[nxt][ns] <= cdist + cost) continue;
			pq2.erase({ d2[nxt][ns], nxt, ns });
			pq2.insert({ d2[nxt][ns] = cdist + cost, nxt, ns });
		}
	}
	if (d2[n][1] >> 30) cout << -1 << '\n';
	else cout << d2[n][0] + d2[n][1] << '\n';
}