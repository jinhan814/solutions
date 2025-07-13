#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
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
	int sz = 1'000'000;
	fenwick l0(sz), l1(sz), r0(sz), r1(sz);
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
			l0.update(sz + 1 - r, r - l);
			l1.update(sz + 1 - r, i64(r - l) * r);
		}
		i64 res_l = l1.query(sz + 1 - s) - s * l0.query(sz + 1 - s);
		i64 res_r = e * r0.query(e) - r1.query(e);
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