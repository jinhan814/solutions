#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(sz + 1) {}
	void update(int i, int x) {
		for (i++; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		if (i < 0) return 0;
		if (i > sz - 1) i = sz - 1;
		int ret = 0;
		for (i++; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int l, int r, const auto& adj) {
	vector sz(n + 1, 0), c(n + 1, 0);
	auto get_sz = [&](const auto& self, int cur, int prv) -> int {
		int& ret = sz[cur] = 1;
		for (int nxt : adj[cur]) {
			if (nxt == prv || c[nxt]) continue;
			ret += self(self, nxt, cur);
		}
		return ret;
	};
	auto get_cent = [&](const auto& self, int cur, int prv, int lim) -> int {
		for (int nxt : adj[cur]) {
			if (nxt == prv || c[nxt]) continue;
			if (sz[nxt] > lim) return self(self, nxt, cur, lim);
		}
		return cur;
	};

	auto res = 0LL;
	fenwick tree(n);
	auto update = [&](int cur) {
		tree.update(0, 1);
		vector buc(0, 0);
		for (int nxt : adj[cur]) {
			if (c[nxt]) continue;
			vector d(0, 0);
			auto dfs = [&](const auto& self, int cur, int prv, int dep) -> void {
				d.push_back(dep);
				res += tree.query(l - dep, r - dep);
				for (int nxt : adj[cur]) {
					if (nxt == prv || c[nxt]) continue;
					self(self, nxt, cur, dep + 1);
				}
			};
			dfs(dfs, nxt, cur, 1);
			for (int dep : d) tree.update(dep, 1), buc.push_back(dep);
		}
		tree.update(0, -1);
		for (int dep : buc) tree.update(dep, -1);
	};

	vector q(1, 1);
	while (q.size()) {
		int x = q.back(); q.pop_back();
		int s = get_sz(get_sz, x, -1);
		int cent = get_cent(get_cent, x, -1, s / 2);
		update(cent);
		c[cent] = 1;
		for (int nxt : adj[cent]) if (!c[nxt]) q.push_back(nxt);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, l, r; cin >> n >> l >> r;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		auto res = sol(n, n - 1 - r, n - 1 - l, adj);
		cout << res << '\n';
	}
}