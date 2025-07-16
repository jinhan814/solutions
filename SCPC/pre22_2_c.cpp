#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](const auto& adj) {
	const int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto rec = [&](const auto& self, int cur) -> int {
		int ret = dfn[cur] = ++dfs_cnt;
		s.push_back(cur);
		for (int nxt : adj[cur]) {
			if (!dfn[nxt]) ret = min(ret, self(self, nxt));
			else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
		}
		if (ret == dfn[cur]) {
			scc_cnt++;
			while (s.size()) {
				int x = s.back(); s.pop_back();
				scc[x] = scc_cnt;
				if (x == cur) break;
			}
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) if (!dfn[i]) rec(rec, i);
	return pair(scc_cnt, scc);
};

auto sol = [](int n, int m, int k, auto e) {
	if (k == -1) {
		vector adj(n + 1, vector(0, 0));
		for (auto [a, b, c] : e) adj[a].push_back(b);
		auto [scc_cnt, scc] = get_scc(adj);
		vector mask(scc_cnt + 1, 0);
		vector scc_adj(scc_cnt + 1, vector(0, pair(0, 0)));
		for (auto [a, b, c] : e) {
			if (scc[a] == scc[b]) mask[scc[a]] |= 1 << c - 'A';
			else scc_adj[scc[a]].push_back(pair(scc[b], c - 'A'));
		}
		vector dp(scc_cnt + 1, array{ 0, 0, 0 });
		for (int i = scc_cnt; i >= 1; i--) {
			if (mask[i] == 7) return -1;
			for (int iter = 0; iter < 2; iter++) {
				for (int x = 0; x < 3; x++) {
					if (~mask[i] >> x & 1) continue;
					int px = x ? x - 1 : 2;
					dp[i][x] = max(dp[i][x], dp[i][px] + 1);
				}
			}
			for (auto [j, x] : scc_adj[i]) {
				int px = x ? x - 1 : 2;
				dp[j][x] = max(dp[j][x], dp[i][px] + 1);
				for (int k = 0; k < 3; k++) {
					dp[j][k] = max(dp[j][k], dp[i][k]);
				}
			}
		}
		int ret = 0;
		for (int i = 1; i <= scc_cnt; i++) {
			int val = max({ dp[i][0], dp[i][1], dp[i][2] });
			ret = max(ret, val);
		}
		return ret;
	}
	else {
		vector adj(3 * n + 1, vector(0, 0));
		auto f = [&](int i, int x) { return 3 * (i - 1) + x + 1; };
		for (auto [a, b, c] : e) {
			int x = c - 'A';
			int px = x ? x - 1 : 2;
			adj[f(a, px)].push_back(f(b, x));
		}
		auto [scc_cnt, scc] = get_scc(adj);
		if (scc_cnt != 3 * n) return -1;
		vector rev(3 * n + 1, 0);
		for (int i = 1; i <= 3 * n; i++) rev[scc[i]] = i;
		int ret = 0;
		vector dp(3 * n + 1, 0);
		for (int iter = 0; iter < k + 1; iter++) {
			vector ndp(3 * n + 1, 0);
			for (auto [a, b, c] : e) {
				for (int x = 0; x < 3; x++) {
					ndp[f(b, x)] = max(ndp[f(b, x)], dp[f(a, x)]);
				}
			}
			for (int i = 3 * n; i >= 1; i--) {
				for (int j : adj[rev[i]]) {
					ndp[j] = max(ndp[j], ndp[rev[i]] + 1);
				}
			}
			dp.swap(ndp);
			for (int i = 1; i <= 3 * n; i++) ret = max(ret, dp[i]);
		}
		return ret;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, m, k; cin >> n >> m >> k;
		vector e(m, tuple(0, 0, '\0'));
		for (auto& [a, b, c] : e) cin >> a >> b >> c;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, k, e) << '\n';
	}
}