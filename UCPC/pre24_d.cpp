#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, pii(1 << 30, 1 << 30)) {}
	void update(int i, pii x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
	}
	pii query(int l, int r) const {
		pii ret(1 << 30, 1 << 30);
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<pii> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	vector idx(n + 1, 0);
	iota(idx.begin() + 1, idx.end(), 1);
	sort(idx.begin() + 1, idx.end(), [&](int i, int j) {
		return a[i] < a[j];
	});
	segtree tree(n);
	for (int i = 1; i <= n; i++) {
		tree.update(i, pii(b[idx[i]], i));
	}
	vector res(n + 1, array{ -1, -1 });
	auto rec = [&](const auto& self, int l, int r, int dep) -> int {
		if (l > r) return -1;
		auto [d, i] = tree.query(l, r);
		if (d != dep) cout << -1 << '\n', exit(0);
		int x = self(self, l, i - 1, dep + 1);
		int y = self(self, i + 1, r, dep + 1);
		if (x != -1) res[idx[i]][0] = idx[x];
		if (y != -1) res[idx[i]][1] = idx[y];
		return i;
	};
	rec(rec, 1, n, 1);
	for (int i = 1; i <= n; i++) {
		cout << res[i][0] << ' ' << res[i][1] << '\n';
	}
}