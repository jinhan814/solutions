#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1) {}
	void update(int i, int x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	int query(int l, int r) const {
		int ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto v) {
	vector buc(n + 1, vector(0, 0));
	for (int i = 0; i < n; i++) buc[v[i]].push_back(i);
	vector nxt(n, -1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < buc[i].size() / 2; j++) {
			int a = buc[i][j];
			int b = buc[i][buc[i].size() - 1 - j];
			nxt[a] = b;
		}
	}
	i64 ret = 0;
	segtree tree(n);
	for (int i = 0; i < n; i++) {
		if (nxt[i] == -1) continue;
		ret += nxt[i] - i - tree.query(i, nxt[i]);
		tree.update(nxt[i], 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}