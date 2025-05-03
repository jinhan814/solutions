#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, i64 x) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] += x;
				push(node, node_l, node_r);
				return;
			}
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = tree[node << 1] + tree[node << 1 | 1];
		};
		dfs(dfs, 1, 1, sz);
	}
	i64 query(int l, int r) {
		auto dfs = [&](const auto& self, int node, int node_l, int node_r) -> i64 {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return 0;
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = node_l + node_r >> 1;
			i64 res_l = self(self, node << 1, node_l, mid);
			i64 res_r = self(self, node << 1 | 1, mid + 1, node_r);
			return res_l + res_r;
		};
		return dfs(dfs, 1, 1, sz);
	}
private:
	int sz;
	vector<i64> tree;
	vector<i64> lazy;
	void push(int i, int l, int r) {
		tree[i] += (r - l + 1) * lazy[i];
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		lazy[i] = 0;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, q; cin >> n >> q;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		vector queries(q, array{ 0, 0, 0 });
		for (auto& [l, r, d] : queries) cin >> l >> r >> d;

		vector buc(n + 1, vector(0, pair(0, 0)));
		buc[n].push_back({ n, v[n] });
		for (int i = n - 1; i >= 1; i--) {
			buc[i].push_back({ i, v[i] });
			for (auto [j, g] : buc[i + 1]) {
				g = gcd(g, v[i]);
				if (buc[i].back().second == g) buc[i].pop_back();
				buc[i].push_back({ j, g });
			}
		}

		vector data(1'000'001, vector(0, array{ 0, 0, 0 }));
		for (int i = 1; i <= n; i++) {
			int prv = i;
			for (auto [j, g] : buc[i]) {
				data[g].push_back({ i, prv, j });
				prv = j + 1;
			}
		}

		vector q_buc(1'000'001, vector(0, 0));
		for (int i = 0; i < q; i++) {
			auto [l, r, d] = queries[i];
			q_buc[d].push_back(i);
		}

		for (int d = 1; d <= 1'000'000; d++) {
			sort(q_buc[d].begin(), q_buc[d].end(), [&](int i, int j) {
				return queries[i][0] > queries[j][0]; });
			sort(data[d].begin(), data[d].end(), [&](auto& a, auto& b) {
				return a[0] > b[0]; });
		}

		vector res(q, 0LL);
		segtree tree(n);
		for (int d = 1; d <= 1'000'000; d++) {
			if (q_buc[d].empty()) continue;
			int pos = 0;
			for (int i : q_buc[d]) {
				auto [l, r, _] = queries[i];
				while (pos < data[d].size() && data[d][pos][0] >= l) {
					auto [i, a, b] = data[d][pos++];
					tree.update(a, b, 1);
				}
				res[i] = tree.query(l, r);
			}
			while (pos) {
				auto [i, a, b] = data[d][--pos];
				tree.update(a, b, -1);
			}
		}
		for (int i = 0; i < q; i++) cout << res[i] << '\n';
	}
}