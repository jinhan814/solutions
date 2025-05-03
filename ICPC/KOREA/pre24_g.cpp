#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b];
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

struct rmu { // range min update, point query
	rmu(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, 1 << 30) {}
	void update(int l, int r, int x) {
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) tree[l] = min(tree[l], x), l++;
			if (~r & 1) tree[r] = min(tree[r], x), r--;
		}
	}
	int query(int i) const {
		int res = 1 << 30;
		--i |= sz;
		do res = min(res, tree[i]); while (i >>= 1);
		return res;
	}
private:
	int sz;
	vector<int> tree;
};

struct rmq { // point update, range max query
	rmq(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, -(1 << 30)) {}
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		int ret = -(1 << 30);
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

auto get_hld = [](auto adj) {
	const int n = adj.size() - 1;
	int ord = 0;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
	vector in(n + 1, 0), top(n + 1, 0);
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
	};
	dfs1(dfs1, 1, 0);
	dfs2(dfs2, top[1] = 1);
	return tuple(dep, par, in, top);
};

auto get_mst = [](int n, int m, auto e) {
	union_find uf(n + 1);
	vector adj(n + 1, vector(0, 0));
	sort(e.begin(), e.end());
	for (auto [c, a, b] : e) {
		if (!uf.merge(a, b)) continue;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	return adj;
};

auto sol = [](int n, int m, auto e) {
	auto adj = get_mst(n, m, e);
	auto [dep, par, in, top] = get_hld(adj);
	rmq tree(n);
	rmu dp(n);
	auto query = [&](int a, int b) {
		int ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			ret = max(ret, tree.query(in[top[a]], in[a]));
			a = par[top[a]];
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret = max(ret, tree.query(in[a] + 1, in[b]));
		return ret;
	};
	auto update = [&](int a, int b, int x) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			dp.update(in[top[a]], in[a], x);
			a = par[top[a]];
		}
		if (dep[a] > dep[b]) swap(a, b);
		dp.update(in[a] + 1, in[b], x);
	};
	for (auto [c, a, b] : e) {
		if (par[b] == a) swap(a, b);
		if (par[a] != b) update(a, b, c);
		else tree.update(in[a], c);
	}
	vector res(m, 0);
	for (int i = 0; i < m; i++) {
		auto [c, a, b] = e[i];
		if (par[b] == a) swap(a, b);
		if (par[a] != b) res[i] = query(a, b) ^ c ? 3 : 2;
		else res[i] = dp.query(in[a]) ^ c ? 1 : 2;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0, 0 });
	for (auto& [c, a, b] : e) cin >> a >> b >> c;
	auto res = sol(n, m, e);
	for (int x : res) cout << x << '\n';
}