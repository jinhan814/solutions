#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] = max(tree[i], x);
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret = max(ret, tree[i]);
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, auto a, auto b, auto x) {
	vector pa(n + 1, 0LL), pb(n + 1, 0LL);
	for (int i = 0; i < n; i++) {
		pa[i + 1] = pa[i] + a[i];
		pb[i + 1] = pb[i] + b[i];
	}
	vector c = pb;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector idx(0, 0);
	for (int i = 1; i <= n; i++) {
		if (pa[i] > 0) continue;
		if (pb[i] < 0) continue;
		idx.push_back(i);
	}
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		if (pa[i] != pa[j]) return pa[i] > pa[j];
		return pb[i] < pb[j];
	});
	i64 ret = 0;
	fenwick tree(c.size());
	for (int i : idx) {
		int p = lower_bound(c.begin(), c.end(), pb[i]) - c.begin() + 1;
		i64 val = tree.query(p) + x[i - 1];
		tree.update(p, val);
		ret = max(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0), x(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> x[i];
	cout << sol(n, a, b, x) << '\n';
}