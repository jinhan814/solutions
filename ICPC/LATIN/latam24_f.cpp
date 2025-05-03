#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector par(n + 1, 0), dep(n + 1, 0), sz(n + 1, 1);
	vector top(n + 1, 0);
	auto dfs1 = [&](const auto& self, int cur, int prv) -> void {
		if (prv) adj[cur].erase(ranges::find(adj[cur], prv));
		for (int& nxt : adj[cur]) {
			par[nxt] = cur;
			dep[nxt] = dep[cur] + 1;
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
			if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
		}
	};
	auto dfs2 = [&](const auto& self, int cur) -> void {
		for (int nxt : adj[cur]) {
			top[nxt] = nxt == adj[cur][0] ? top[cur] : nxt;
			self(self, nxt);
		}
	};
	dfs1(dfs1, 1, 0);
	dfs2(dfs2, top[1] = 1);

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

	auto query = [&](int a, int b, int c) -> int {
		int ab = lca(a, b), ac = lca(a, c), bc = lca(b, c), l = lca(ab, c);
		int p = l == a ? bc : l == b ? ac : l == c ? ab : ab != l ? ab : ac != l ? ac : bc;
		int x = dist(a, p), y = dist(b, p), z = dist(c, p);
		if (x > y) swap(x, y);
		if (x > z) swap(x, z);
		return y + z + 1 >> 1;
	};

	int q; cin >> q;
	while (q--) {
		int a, b, c; cin >> a >> b >> c;
		cout << query(a, b, c) << '\n';
	}
}