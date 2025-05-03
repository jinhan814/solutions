#include <bits/stdc++.h>
using namespace std;

template<int sz>
struct segtree {
	segtree() { tree.set(); }
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] | tree[i << 1 | 1];
	}
	int get_nxt(int i) const {
		--i |= sz;
		while (!tree[i]) i = i + 1 >> 1;
		while (i < sz) i = i << 1 | !tree[i << 1];
		return i - sz + 1;
	}
private:
	bitset<sz << 1> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	segtree<1 << 20> tree;
	for (int i = 1; i <= q; i++) {
		int t, x; cin >> t >> x;
		if (t == 1) {
			int p = tree.get_nxt(x);
			if (p == n + 1) cout << -1 << '\n';
			else cout << p << '\n', v[p] = i, tree.update(p, 0);
		}
		else {
			if (!v[x]) cout << -1 << '\n';
			else cout << v[x] << '\n', v[x] = 0, tree.update(x, 1);
		}
	}
}