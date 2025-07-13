#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1) {}
	void update(int i, i64 x) {
		--i |= sz;
		do tree[i] += x; while (i >>= 1);
	}
	i64 query(int l, int r) const {
		i64 ret = 0;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	vector q_idx(q, 0);
	iota(q_idx.begin(), q_idx.end(), 0);
	sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
		return a[0] + a[1] < b[0] + b[1];
	});
	sort(q_idx.begin(), q_idx.end(), [&](int i, int j) {
		return qs[i][0] + qs[i][1] < qs[j][0] + qs[j][1];
	});
	segtree l0(1'000'000), l1(1'000'000);
	segtree r0(1'000'000), r1(1'000'000);
	for (auto [l, r] : v) {
		r0.update(l, r - l);
		r1.update(l, i64(r - l) * l);
	}
	vector res(q, 0LL);
	int pos = 0;
	for (int i : q_idx) {
		auto [s, e] = qs[i];
		while (pos < n && v[pos][0] + v[pos][1] <= s + e) {
			auto [l, r] = v[pos++];
			r0.update(l, -(r - l));
			r1.update(l, -i64(r - l) * l);
			l0.update(r, r - l);
			l1.update(r, i64(r - l) * r);
		}
		i64 res_l0 = l0.query(s, 1'000'000);
		i64 res_l1 = l1.query(s, 1'000'000);
		i64 res_r0 = r0.query(1, e);
		i64 res_r1 = r1.query(1, e);
		i64 res_l = res_l1 - s * res_l0;
		i64 res_r = e * res_r0 - res_r1;
		res[i] = res_l + res_r;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, array{ 0, 0 });
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << 2 * res[i] << '\n';
}