#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << 17), tree(sz << 1) {}
	void update(int i, i64 x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
	}
	i64 query(int l, int r) {
		i64 ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];

	vector p(n + 1, 0LL);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + v[i];

	vector a(n, -1), b(n, -1);
	segtree tree(n);
	for (int i = 0, j = 0; i < n; i = j) {
		if (v[i] >= 0) { j++; continue; }
		while (j < n && v[j] < 0) j++;
		for (int k = i; k < j; k++) a[k] = i, b[k] = j - 1;
		tree.update(i, p[j] - p[i]);
	}

	auto query = [&](int l, int r) -> i64 {
		if (a[l] == -1 && a[r] == -1) return tree.query(l, r);
		if (a[l] == a[r]) return p[r + 1] - p[l];
		if (a[l] == -1) return min(tree.query(l, a[r] - 1), p[r + 1] - p[a[r]]);
		if (a[r] == -1) return min(tree.query(b[l] + 1, r), p[b[l] + 1] - p[l]);
		return min({ tree.query(b[l] + 1, a[r] - 1), p[b[l] + 1] - p[l], p[r + 1] - p[a[r]] });
	};

	for (int i = 0; i < n; i++) cout << query(max(0, i - m + 1), i) << ' ';
	cout << '\n';
}