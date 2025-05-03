#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector par(n + 1, -1), dep(n + 1, 0);
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		par[cur] = prv;
		for (int nxt : adj[cur]) {
			if (par[nxt] != -1) continue;
			dep[nxt] = dep[cur] + 1;
			self(self, nxt, cur);
		}
	};
	dfs(dfs, 1, 0);

	vector g(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		vector buc(0, 0);
		for (int j : adj[i]) {
			if (dep[j] == dep[i] + 1) continue;
			buc.push_back(j);
		}
		for (int j : buc) {
			adj[i].erase(ranges::find(adj[i], j));
			if (dep[j] >= dep[i] - 1) continue;
			g[j].push_back(i);
		}
	}

	vector c(n + 1, -1), v(0, 0);
	for (int i = 1; i <= n; i++) {
		for (int j : g[i]) {
			if (c[j] != -1) continue;
			c[j] = v.size();
			v.push_back(j);
		}
	}

	vector dp(n + 1, vector(2, vector(1 << v.size(), -1)));
	auto rec = [&](const auto& self, int cur, int col, int s) -> int {
		int& ret = dp[cur][col][s];
		if (ret != -1) return ret;
		if (c[cur] != -1 && s >> c[cur] & 1 ^ col) return ret = -(1 << 30);
		for (int nxt : g[cur]) {
			if (col && s >> c[nxt] & 1)
				return ret = -(1 << 30);
		}
		ret = col;
		for (int nxt : adj[cur]) {
			int res = self(self, nxt, 0, s);
			if (!col) res = max(res, self(self, nxt, 1, s));
			if (res < 0) return ret = -(1 << 30);
			ret += res;
		}
		return ret;
	};

	int res = 0;
	for (int s = 0; s < 1 << v.size(); s++) {
		res = max(res, rec(rec, 1, 0, s));
		res = max(res, rec(rec, 1, 1, s));
	}
	cout << res << '\n';
}