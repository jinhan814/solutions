#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

auto get_hld = [](auto& adj) { // 1-indexed
	const int n = adj.size() - 1;
	int ord = 0;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
	vector in(n + 1, 0), out(n + 1, 0), top(n + 1, 0);
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
		in[cur] = ++ord;
		for (int nxt : adj[cur]) {
			top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
			self(self, nxt);
		}
		out[cur] = ord;
	};
	dfs1(dfs1, 1, 0);
	dfs2(dfs2, top[1] = 1);
	return tuple(dep, par, in, top);
};

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1) {}
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		int ret = 0;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

int main() {
	fastio;
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	auto [dep, par, in, top] = get_hld(adj);
	vector r_in(n + 1, 0);
	for (int i = 1; i <= n; i++) r_in[in[i]] = i;

	vector dp1(n + 1, 0);
	vector dp2(n + 1, 0);
	vector dp3(n + 1, 0);
	vector buc(n + 1, multiset{ 0 });
	{
		auto dfs1 = [&](const auto& self, int cur) -> void {
			for (int nxt : adj[cur]) {
				self(self, nxt);
				dp1[cur] = max(dp1[cur], dp1[nxt] + 1);
				buc[cur].insert(dp1[nxt] + 1);
				if (top[nxt] != nxt) continue;
				dp2[cur] = max(dp2[cur], dp1[nxt] + 1);
			}
		};
		auto dfs2 = [&](const auto& self, int cur, int val) -> void {
			dp3[cur] = val;
			for (int nxt : adj[cur]) {
				buc[cur].erase(buc[cur].find(dp1[nxt] + 1));
				self(self, nxt, max(val, *prev(buc[cur].end())) + 1);
				buc[cur].insert(dp1[nxt] + 1);
			}
		};
		dfs1(dfs1, 1);
		dfs2(dfs2, 1, 0);
	}

	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update(in[i], dp2[i]);

	auto get = [&](int a, int b) {
		int ret = 0, pa = -1, pb = -1;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b), swap(pa, pb);
			ret = max(ret, tree.query(in[top[a]], in[a] - 1));
			if (pa != -1) buc[a].erase(buc[a].find(pa));
			ret = max(ret, *prev(buc[a].end()));
			if (pa != -1) buc[a].insert(pa);
			pa = dp1[top[a]] + 1;
			a = par[top[a]];
		}
		if (dep[a] < dep[b]) swap(a, b), swap(pa, pb);
		ret = max(ret, tree.query(in[b] + 1, in[a] - 1));
		if (a != b) {
			if (pa != -1) buc[a].erase(buc[a].find(pa));
			ret = max(ret, *prev(buc[a].end()));
			if (pa != -1) buc[a].insert(pa);
			if (pb != -1) buc[b].erase(buc[b].find(pb));
			buc[b].erase(buc[b].find(dp1[r_in[in[b] + 1]] + 1));
			ret = max(ret, *prev(buc[b].end()));
			if (pb != -1) buc[b].insert(pb);
			buc[b].insert(dp1[r_in[in[b] + 1]] + 1);
		}
		else {
			if (pa != -1) buc[a].erase(buc[a].find(pa));
			if (pb != -1) buc[a].erase(buc[a].find(pb));
			ret = max(ret, *prev(buc[a].end()));
			if (pa != -1) buc[a].insert(pa);
			if (pb != -1) buc[a].insert(pb);
		}
		ret = max(ret, dp3[b]);
		return ret;
	};

	auto lca = [&](int a, int b) -> int {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			a = par[top[a]];
		}
		return dep[a] < dep[b] ? a : b;
	};

	auto dist = [&](int a, int b) -> int {
		int u = lca(a, b);
		return dep[a] + dep[b] - 2 * dep[u];
	};

	auto query = [&](int a, int b) -> int {
		int r1 = dist(a, b);
		int r2 = get(a, b);
		return r1 + 2 * r2;
	};

	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		cout << query(a, b) << '\n';
	}
}