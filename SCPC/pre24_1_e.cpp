#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector idx(q, 0);
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		if ((qs[i][0] ^ qs[j][0]) >> 8) return qs[i][0] < qs[j][0];
		if (qs[i][0] >> 8 & 1) return qs[i][1] < qs[j][1];
		return qs[i][1] > qs[j][1];
	});
	int acc = 0;
	vector cnt(n + 1, 0);
	auto push = [&](i64 x) {
		if (x < 2) return;
		for (; x <= n; x = x * x) {
			if (++cnt[x] % x) break;
			acc++;
		}
	};
	auto pop = [&](i64 x) {
		if (x < 2) return;
		for (; x <= n; x = x * x) {
			if (cnt[x]-- % x) break;
			acc--;
		}
	};
	vector res(q, 0);
	for (int cl = 0, cr = -1; int i : idx) {
		auto [l, r] = qs[i];
		while (cl > l) push(v[--cl]);
		while (cr < r) push(v[++cr]);
		while (cl < l) pop(v[cl++]);
		while (cr > r) pop(v[cr--]);
		res[i] = acc;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		int q; cin >> q;
		vector qs(q, array{ 0, 0 });
		for (auto& [l, r] : qs) cin >> l >> r;
		auto res = sol(n, q, v, qs);
		cout << "Case #" << tc_num << '\n';
		for (int x : res) cout << x << '\n';
	}
}