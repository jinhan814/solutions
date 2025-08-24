#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, int s, int t, const auto& v) {
	int p = 0;
	for (int i = 1; i < n; i++) {
		int d1 = abs(v[p][0] - s);
		int d2 = abs(v[i][0] - s);
		if (d1 > d2 || d1 == d2 && v[p][1] >= v[i][1]) p = i;
	}
	vector cand{ array{ s + abs(v[p][0] - s), v[p][1] } };
	for (int i = p + 1; i < n; i++) {
		if (cand.back()[0] >= v[i][0]) continue;
		if (cand.back()[1] <= v[i][1]) continue;
		cand.push_back(v[i]);
	}
	vector hull(0, array{ 0LL, 0LL });
	auto f = [&](int x) {
		if (hull.empty()) return 0LL;
		int lo = 0, hi = hull.size() - 1;
		while (hi - lo >= 3) {
			int mid = lo + hi >> 1;
			auto [a1, b1] = hull[mid];
			auto [a2, b2] = hull[mid + 1];
			if (a1 * x + b1 > a2 * x + b2) lo = mid;
			else hi = mid + 1;
		}
		i64 ret = 1LL << 60;
		for (int i = lo; i <= hi; i++) {
			auto [a, b] = hull[i];
			ret = min(ret, a * x + b);
		}
		return ret;
	};
	auto push = [&](i64 a, i64 b) {
		while (hull.size() >= 2) {
			auto [a1, b1] = hull[hull.size() - 1];
			auto [a2, b2] = hull[hull.size() - 2];
			if ((b1 - b2) * (a1 - a) < (b - b1) * (a2 - a1)) break;
			hull.pop_back();
		}
		hull.push_back({ a, b });
	};
	for (int iter = 0; iter < cand.size(); iter++) {
		i64 x = cand[iter][0];
		i64 w = cand[iter][1];
		int l = max(s, int(x + s - abs(cand[0][0] - s) + 1) / 2);
		int r = max(s, int(x));
		push(w, f(l) + (x - 2 * l) * w);
		push(w, f(r) + (x - 2 * r) * w);
	}
	i64 r1 = abs(v[p][0] - s) + abs(s - t);
	i64 r2 = f(t);
	return array{ r1, r2 };
};

auto sol = [](int n, int q, auto v, auto qs) {
	int mx = 0;
	for (int i = 0; i < n; i++) mx = max(mx, v[i][0]);
	for (auto [a, b] : qs) mx = max(mx, max(a, b));
	vector res(q, array{ 0LL, 0LL });
	sort(v.begin(), v.end());
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		if (a < b) res[i] = calc(n, a, b, v);
	}
	for (int i = 0; i < n; i++) v[i][0] = mx - v[i][0];
	sort(v.begin(), v.end());
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		if (a > b) res[i] = calc(n, mx - a, mx - b, v);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a;
		for (auto& [a, b] : v) cin >> b;
		int q; cin >> q;
		vector qs(q, array{ 0, 0 });
		for (auto& [a, b] : qs) cin >> a >> b;
		auto res = sol(n, q, v, qs);
		cout << "Case #" << tc_num << '\n';
		for (auto [x, y] : res) cout << x << ' ' << y << '\n';
	}
}