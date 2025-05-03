#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) :
		sz(1 << __lg(n - 1) + 1),
		tree1(sz << 1), tree2(sz << 1),
		lazy1(sz << 1), lazy2(sz << 1) {}
	void update1(int l, int r, int x) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy2[node] += x;
				push(node, node_l, node_r);
				return;
			}
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree1[node] = tree1[node << 1] + tree1[node << 1 | 1];
			tree2[node] = tree2[node << 1] + tree2[node << 1 | 1];
		};
		dfs(dfs, 1, 1, sz);
	}
	void update2(int l, int r, i64 x) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy1[node] = 1;
				lazy2[node] = x;
				push(node, node_l, node_r);
				return;
			}
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree1[node] = tree1[node << 1] + tree1[node << 1 | 1];
			tree2[node] = tree2[node << 1] + tree2[node << 1 | 1];
		};
		dfs(dfs, 1, 1, sz);
	}
	pair<i64, i64> query(int l, int r) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> pair<i64, i64> {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return { 0, 0 };
			if (l <= node_l && node_r <= r) return { tree1[node], tree2[node] };
			int mid = node_l + node_r >> 1;
			auto [l1, l2] = self(self, node << 1, node_l, mid);
			auto [r1, r2] = self(self, node << 1 | 1, mid + 1, node_r);
			return { l1 + r1, l2 + r2 };
		};
		return dfs(dfs, 1, 1, sz);
	}
private:
	int sz;
	vector<i64> tree1;  // a[i]
	vector<i64> tree2;  // i * a[i]
	vector<bool> lazy1; // range_set
	vector<i64> lazy2;  // range_add
	void push(int i, int l, int r) {
		if (lazy1[i]) {
			tree1[i] = i64(r - l + 1) * lazy2[i];
			tree2[i] = i64(r + l) * (r - l + 1) * lazy2[i] >> 1;
			if (l != r) {
				lazy1[i << 1] = lazy1[i];
				lazy1[i << 1 | 1] = lazy1[i];
				lazy2[i << 1] = lazy2[i];
				lazy2[i << 1 | 1] = lazy2[i];
			}
			lazy1[i] = 0;
			lazy2[i] = 0;
		}
		else {
			tree1[i] += i64(r - l + 1) * lazy2[i];
			tree2[i] += i64(r + l) * (r - l + 1) * lazy2[i] >> 1;
			if (l != r) {
				lazy2[i << 1] += lazy2[i];
				lazy2[i << 1 | 1] += lazy2[i];
			}
			lazy2[i] = 0;
		}
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	segtree tree(n);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		tree.update1(i, i, x);
	}
	while (q--) {
		int t, l, r, x; cin >> t >> l >> r;
		if (t == 1) {
			cin >> x;
			tree.update1(l, r, x);
		}
		else if (t == 2) {
			cin >> x;
			tree.update2(l, r, x);
		}
		else if (t == 3) {
			auto [a, b] = tree.query(l, r);
			b -= a * (l - 1);
			bool res = a ? b % a == 0 && 1 <= b / a && b / a <= (r - l + 1) : !b;
			cout << (res ? "Yes" : "No") << '\n';
		}
	}
}