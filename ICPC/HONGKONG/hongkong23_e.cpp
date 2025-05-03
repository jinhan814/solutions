#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, { 0, 1 }), lazy(sz << 1) {
		for (int i = sz - 1; i >= 1; i--)
			tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}
	void update(int l, int r, int x) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (r < node_l || node_r < l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] += x;
				push(node, node_l, node_r);
				return;
			}
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
		};
		dfs(dfs, 1, 1, sz);
	}
	int query(int l, int r) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> pii {
			push(node, node_l, node_r);
			if (r < node_l || node_r < l) return pii(1 << 30, 0);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = node_l + node_r >> 1;
			auto r1 = self(self, node << 1, node_l, mid);
			auto r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return merge(r1, r2);
		};
		auto res = dfs(dfs, 1, 1, sz);
		return res.first ? 0 : res.second;
	}
private:
	int sz;
	vector<pii> tree;
	vector<int> lazy;
	pii merge(const pii& a, const pii& b) const {
		if (a.first != b.first) return min(a, b);
		return pii(a.first, a.second + b.second);
	}
	void push(int i, int l, int r) {
		if (!lazy[i]) return;
		tree[i].first += lazy[i];
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		lazy[i] = 0;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];

	vector buc(1'000'001, vector(0, 0));
	for (int i = 1; i <= n; i++) buc[v[i]].push_back(i);

	vector in(n + 1, vector(0, pii{ 0, 0 }));
	vector out(n + 1, vector(0, pii{ 0, 0 }));
	for (auto& t : buc) {
		if (t.size() < k) continue;
		for (int i = k - 1; i < t.size(); i++) {
			int l1 = i - k >= 0 ? t[i - k] + 1 : 1;
			int l2 = t[i - k + 1];
			int r1 = t[i];
			int r2 = i + 1 < t.size() ? t[i + 1] - 1 : n;
			in[l1].push_back({ r1, r2 });
			out[l2].push_back({ r1, r2 });
		}
	}

	segtree tree(n);
	auto res = 0LL;
	for (int i = 1; i <= n; i++) {
		for (auto [l, r] : in[i]) tree.update(l, r, 1);
		res += tree.query(i, n);
		for (auto [l, r] : out[i]) tree.update(l, r, -1);
	}
	cout << res << '\n';
}