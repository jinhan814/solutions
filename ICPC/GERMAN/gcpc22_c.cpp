#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;

	fenwick tree(n);
	auto query = [&](int l, int r) -> bool {
		if (l > r) swap(l, r);
		if (tree.query(l, r) == 0) return 1;
		if (tree.query(1, l) + tree.query(r, n) == 0) return 1;
		return 0;
	};

	while (q--) {
		char c; int a, b; cin >> c >> a;
		if (c == '-') tree.update(a, 1);
		else if (c == '+') tree.update(a, -1);
		else cin >> b, cout << (query(a, b) ? "possible" : "impossible") << '\n';
	}
}