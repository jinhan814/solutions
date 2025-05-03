#include <bits/stdc++.h>
using namespace std;

template<int sz>
struct segtree {
	void update(int i) {
		tree[--i |= sz].flip();
		while (i >>= 1) tree[i] = tree[i << 1] & tree[i << 1 | 1];
	}
	int query(int i) const {
		--i |= sz;
		while (tree[i]) i = ++i >> 1;
		while (i < sz) i = i << 1 | tree[i << 1];
		return i - sz + 1;
	}
private:
	bitset<sz << 1> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	segtree<1 << 21> tree;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		tree.update(v[i]);
	}
	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		int res = tree.query(v[x]);
		tree.update(v[x]);
		tree.update(v[x] = res);
		cout << res << '\n';
	}
}