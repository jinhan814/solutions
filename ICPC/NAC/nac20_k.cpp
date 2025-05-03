#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto get_hld = [](auto& adj) { // 1-indexed
	const int n = adj.size() - 1;
	int ord = 0;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0), top(n + 1, 0);
	auto dfs1 = [&](const auto& self, int cur, int prv) -> void {
		if (prv) adj[cur].erase(ranges::find(adj[cur], prv));
		for (int& nxt : adj[cur]) {
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
			if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
		}
	};
	auto dfs2 = [&](const auto& self, int cur) -> void {
		for (int nxt : adj[cur]) {
			top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
			self(self, nxt);
		}
	};
	dfs1(dfs1, 1, 0);
	dfs2(dfs2, top[1] = 1);
	return tuple(sz, dep, par, top);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto [sz, dep, par, top] = get_hld(adj);
	auto lca = [&](int a, int b) -> int {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			a = par[top[a]];
		}
		return dep[a] < dep[b] ? a : b;
	};
	auto dist = [&](int a, int b) -> int {
		int l = lca(a, b);
		return dep[a] + dep[b] - 2 * dep[l];
	};
	auto query = [&](int a, int b) -> i64 {
		i64 x = dist(a, b) + 1;
		return n - x + x * (x + 1) / 2;
	};
	while (q--) {
		int a, b; cin >> a >> b;
		cout << query(a, b) << '\n';
	}
}