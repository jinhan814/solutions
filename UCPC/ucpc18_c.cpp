#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	vector par(n + 1, 0);
	vector mx_h(n + 1, 0LL);
	vector dp_sub(n + 1, 0LL);
	vector dp_par(n + 1, 0LL);
	auto dfs1 = [&](const auto& self, int cur) -> void {
		for (auto [nxt, cost] : adj[cur]) {
			adj[nxt].erase(ranges::find(adj[nxt], pair(cur, cost)));
			par[nxt] = cur;
			self(self, nxt);
			dp_sub[cur] = max(dp_sub[cur], dp_sub[nxt]);
			dp_sub[cur] = max(dp_sub[cur], mx_h[cur] + mx_h[nxt] + cost);
			mx_h[cur] = max(mx_h[cur], mx_h[nxt] + cost);
		}
	};
	auto dfs2 = [&](const auto& self, int cur, auto mx_par) -> void {
		vector buc_h(0, pair(0LL, 0));
		vector buc_dp(0, pair(0LL, 0));
		for (auto [nxt, cost] : adj[cur]) {
			buc_h.push_back({ mx_h[nxt] + cost, nxt });
			buc_dp.push_back({ dp_sub[nxt], nxt });
		}
		sort(buc_h.begin(), buc_h.end(), greater{});
		sort(buc_dp.begin(), buc_dp.end(), greater{});
		while (buc_h.size() > 3) buc_h.pop_back();
		while (buc_dp.size() > 2) buc_dp.pop_back();
		for (auto [nxt, cost] : adj[cur]) {
			dp_par[nxt] = max(dp_par[cur], mx_par);
			for (auto [v1, x] : buc_dp) {
				if (x == nxt) continue;
				dp_par[nxt] = max(dp_par[nxt], v1);
			}
			for (auto [v1, x] : buc_h) {
				if (x == nxt) continue;
				dp_par[nxt] = max(dp_par[nxt], mx_par + v1);
				for (auto [v2, y] : buc_h) {
					if (y <= x || y == nxt) continue;
					dp_par[nxt] = max(dp_par[nxt], v1 + v2);
				}
			}
			auto n_mx_par = mx_par + cost;
			for (auto [v1, x] : buc_h) {
				if (x == nxt) continue;
				n_mx_par = max(n_mx_par, v1 + cost);
			}
			self(self, nxt, n_mx_par);
		}
	};
	dfs1(dfs1, 1);
	dfs2(dfs2, 1, 0LL);

	auto res = 0LL;
	for (int i = 1; i <= n; i++) {
		for (auto [j, cost] : adj[i])
			res = max(res, dp_sub[j] + dp_par[j] + cost);
	}
	cout << res << '\n';
}