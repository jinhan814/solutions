#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	i64 s, l, r, mx;
	node() : node(0) {}
	node(i64 x) : s(x), l(x), r(x), mx(x) {}
	node operator+ (const node& x) const {
		node ret;
		ret.s = s + x.s;
		ret.l = max(l, s + x.l);
		ret.r = max(r + x.s, x.r);
		ret.mx = max({ mx, x.mx, r + x.l });
		return ret;
	}
};

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1) {}
	void update(int i, node x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	i64 query(int l, int r) const {
		node res_l(-(1 << 30)), res_r(-(1 << 30));
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return (res_l + res_r).mx;
	}
private:
	int sz;
	vector<node> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector op(m + 1, array{ 0, 0, 0 });
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 3; j++)
			cin >> op[i][j];
	}
	int q; cin >> q;
	vector queries(q + 1, array{ 0, 0, 0 });
	for (int i = 1; i <= q; i++) {
		for (int j = 0; j < 3; j++)
			cin >> queries[i][j];
	}

	vector idx(q, 0);
	iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		return queries[i][0] < queries[j][0];
	});

	vector buc_plus(n + 1, vector(0, 0));
	vector buc_minus(n + 1, vector(0, 0));
	for (int i = 1; i <= m; i++) {
		buc_plus[op[i][0]].push_back(i);
		buc_minus[op[i][1]].push_back(i);
	}

	segtree tree(m);
	vector res(q + 1, 0LL);
	for (int i = 0, pos = 0; i < q; i++) {
		auto [p, l, r] = queries[idx[i]];
		while (pos < p) {
			for (int x : buc_minus[pos++]) tree.update(x, node());
			for (int x : buc_plus[pos]) tree.update(x, node(op[x][2]));
		}
		res[idx[i]] = tree.query(l, r);
	}
	for (int i = 1; i <= q; i++) cout << res[i] << '\n';
}