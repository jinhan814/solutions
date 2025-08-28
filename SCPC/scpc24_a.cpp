#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, 1 << 30) {}
	void update(int i, int x) {
		i |= sz;
		do tree[i] = min(tree[i], x); while (i >>= 1);
	}
	int query(int l, int r) const {
		int ret = 1 << 30;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int k, auto v) {
	segtree tree(500'001);
	i64 ret = 0;
	for (int i = 0; i < n; i++) {
		int j = tree.query(max(v[i] - k, 0), v[i]);
		if (i > j) ret += i - j;
		tree.update(v[i], i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, k, v) << '\n';
	}
}