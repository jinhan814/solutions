#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](const auto& adj) { // 1-indexed
	const int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto dfs = [&](const auto& self, int cur) -> int {
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
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
	return pair(scc_cnt, scc);
};

auto sol = [](int n, int m, auto v, auto queries) {
	vector idx(n, vector(m, array{ 0, 0, 0, 0 }));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		int x = i * m + j << 2;
		for (int k = 0; k < 4; k++) idx[i][j][k] = x + k + 1;
	}

	auto oob = [&](int x, int y) {
		return x < 0 || x >= n || y < 0 || y >= m;
	};

	vector adj(n * m << 2 | 1, vector(0, 0));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		for (int d = 0; d < 4; d++) {
			int nx = i + "1012"[d] - '1';
			int ny = j + "2101"[d] - '1';
			if (oob(nx, ny) || v[i][j] == v[nx][ny]) continue;
			int nxt = idx[nx][ny][d + 2 & 3];
			for (int k = 0; k < 4; k++) {
				int px = i + "1012"[k] - '1';
				int py = j + "2101"[k] - '1';
				int cur = idx[i][j][k];
				if (!oob(px, py) && v[px][py] == v[nx][ny]) continue;
				adj[cur].push_back(nxt);
			}
		}
	}

	const auto [scc_cnt, scc] = get_scc(adj);
	vector scc_adj(scc_cnt + 1, vector(0, 0));
	vector scc_rev(scc_cnt + 1, vector(0, 0));
	vector scc_sz(scc_cnt + 1, 0);
	for (int i = 1; i < adj.size(); i++) {
		scc_sz[scc[i]]++;
		for (int j : adj[i]) {
			if (scc[i] == scc[j]) continue;
			scc_adj[scc[i]].push_back(scc[j]);
			scc_rev[scc[j]].push_back(scc[i]);
		}
	}

	auto get = [&](int s, int t) {
		vector dp1(scc_cnt + 1, -2);
		dp1[scc[s]] = scc_sz[scc[s]];
		for (int i = scc_cnt; i; i--) {
			if (dp1[i] == -2) continue;
			if (scc_sz[i] > 1) dp1[i] = 1 << 30;
			for (int j : scc_adj[i]) dp1[j] = max(dp1[j], dp1[i] + scc_sz[j]);
			if (dp1[i] >> 30) dp1[i] = -1;
		}

		vector dp2(scc_cnt + 1, -2);
		dp2[scc[t]] = scc_sz[scc[t]];
		for (int i = 1; i <= scc_cnt; i++) {
			if (dp2[i] == -2) continue;
			if (scc_sz[i] > 1) dp2[i] = 1 << 30;
			for (int j : scc_rev[i]) dp2[j] = max(dp2[j], dp2[i] + scc_sz[j]);
			if (dp2[i] >> 30) dp2[i] = -1;
		}

		vector res(queries.size(), -2);
		for (int i = 0; i < queries.size(); i++) {
			auto [x, y] = queries[i];
			for (int d = 0; d < 4; d++) {
				int p = idx[x][y][d];
				int a = dp1[scc[p]];
				int b = dp2[scc[p]];
				if (a == -2 || b == -2) continue;
				if (a == -1 || b == -1) { res[i] = -1; break; }
				res[i] = max(res[i], a + b - 1);
			}
		}
		return res;
	};

	const int s = idx[0][0][2];
	const int t1 = idx[n - 1][m - 1][1];
	const int t2 = idx[n - 1][m - 1][2];
	const auto r1 = get(s, t1);
	const auto r2 = get(s, t2);

	vector res(queries.size(), 0);
	for (int i = 0; i < queries.size(); i++) {
		if (r1[i] == -1 || r2[i] == -1) res[i] = -1;
		else res[i] = max(r1[i], r2[i]);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		vector v(n, string{});
		for (int i = 0; i < n; i++) cin >> v[i];
		int k; cin >> k;
		vector queries(k, pair(0, 0));
		for (auto& [a, b] : queries) cin >> a >> b;
		auto res = sol(n, m, v, queries);
		for (int x : res) cout << x << '\n';
	}
}