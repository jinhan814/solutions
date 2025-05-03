#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](auto adj) {
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

auto sol = [](int n, auto p, auto adj) {
	auto [scc_cnt, scc] = get_scc(adj);
	vector scc_adj(scc_cnt + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) for (int j : adj[i]) {
		if (scc[i] == scc[j]) continue;
		scc_adj[scc[i]].push_back(scc[j]);
	}
	for (auto& g : scc_adj) {
		sort(g.begin(), g.end());
		g.erase(unique(g.begin(), g.end()), g.end());
	}
	vector acc(scc_cnt + 1, 1.l);
	for (int i = 1; i <= n; i++) acc[scc[i]] *= 1 - p[i];
	auto res = 0.l;
	for (int i = 1; i <= scc_cnt; i++) {
		if (scc_adj[i].size()) continue;
		res = max(res, acc[i]);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector p(n + 1, 0.l);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> p[i];
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	cout << setprecision(20);
	cout << sol(n, p, adj) << '\n';
}