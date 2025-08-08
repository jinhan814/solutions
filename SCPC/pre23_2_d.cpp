#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, 1LL << 60) {}
	void update(int i, i64 x) {
		--i |= sz;
		do tree[i] = min(tree[i], x); while (i >>= 1);
	}
	i64 query(int l, int r) const {
		i64 ret = 1LL << 60;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto a, auto b, auto qs) {
	vector buc(n, 0);
	iota(buc.begin(), buc.end(), 1);
	sort(buc.begin(), buc.end(), [&](int i, int j) {
		if (b[i] != b[j]) return b[i] < b[j];
		return i < j;
	});
	set s{ 0 }; s.clear();
	vector vc(n + 1, vector(0, 0));
	vector vq(n + 1, vector(0, 0));
	for (int i : buc) {
		s.insert(i);
		auto lo = s.lower_bound(i);
		auto hi = s.upper_bound(i);
		if (lo != s.begin()) vc[i].push_back(*prev(lo));
		if (hi != s.end()) vc[*hi].push_back(i);
	}
	for (int i = 0; i < q; i++) {
		vq[qs[i][1]].push_back(i);
	}
	segtree tree(n);
	vector res(q, 1LL << 60);
	for (int i = 1; i <= n; i++) {
		for (int j : vc[i]) tree.update(j, i64(a[i] - a[j]) * (b[i] + b[j]));
		for (int j : vq[i]) res[j] = tree.query(qs[j][0], i);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector a(n + 1, 0), b(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
		int q; cin >> q;
		vector qs(q, array{ 0, 0 });
		for (auto& [a, b] : qs) cin >> a >> b;
		auto res = sol(n, q, a, b, qs);
		cout << "Case #" << tc_num << '\n';
		for (int i = 0; i < q; i++) cout << res[i] << '\n';
	}
}