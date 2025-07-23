#include <bits/stdc++.h>
using namespace std;

auto ccw = [](auto a, auto b, auto c) {
	auto x1 = b[0] - a[0];
	auto y1 = b[1] - a[1];
	auto x2 = c[0] - b[0];
	auto y2 = c[1] - b[1];
	auto res = 1LL * x1 * y2 - 1LL * x2 * y1;
	return res ? res > 0 ? 1 : -1 : 0;
};

auto is_cross = [](auto a, auto b) {
	if (a[0] > a[1]) swap(a[0], a[1]);
	if (b[0] > b[1]) swap(b[0], b[1]);
	if (a > b) swap(a, b);
	int a0 = ccw(a[0], a[1], b[0]);
	int a1 = ccw(a[0], a[1], b[1]);
	int b0 = ccw(b[0], b[1], a[0]);
	int b1 = ccw(b[0], b[1], a[1]);
	if (!a0 && !a1 && !b0 && !b1) return b[0] <= a[1];
	return a0 * a1 <= 0 && b0 * b1 <= 0;
};

auto convex_hull = [](auto v) {
	sort(v.begin(), v.end());
	vector u(0, array{ 0, 0 }), d(0, array{ 0, 0 });
	for (auto p : v) {
		while (u.size() > 1 && ccw(u.end()[-2], u.back(), p) >= 0) u.pop_back();
		while (d.size() > 1 && ccw(d.end()[-2], d.back(), p) <= 0) d.pop_back();
		u.push_back(p);
		d.push_back(p);
	}
	for (int i = u.size() - 2; i >= 1; i--) d.push_back(u[i]);
	return d;
};

auto sol = [](int n, int m, int k, auto x, auto y) {
	array a{ 1, 0 }, b{ n, m - 1 }, c{ 0, 1 }, d{ n - 1, m };
	vector lo{ a, b }, hi{ c, d };
	for (int i = 0; i < k; i++) {
		array p1{ x[i], y[i] - 1 };
		array p2{ x[i] - 1, y[i] };
		if (ccw(a, b, p2) < 0) continue;
		if (ccw(c, d, p1) > 0) continue;
		int x1 = ccw(a, b, p1);
		int x2 = ccw(c, d, p2);
		if (x1 == 0 || x2 == 0) return 0;
		if (x1 < 0) lo.push_back(p2);
		if (x2 > 0) hi.push_back(p1);
	}
	lo = convex_hull(lo);
	hi = convex_hull(hi);
	for (int i = 0; i < lo.size(); i++) {
		auto p1 = lo[i];
		auto p2 = lo[i + 1 < lo.size() ? i + 1 : 0];
		auto li = array{ p1, p2 };
		for (int j = 0; j < hi.size(); j++) {
			auto p3 = hi[j];
			auto p4 = hi[j + 1 < hi.size() ? j + 1 : 0];
			auto lj = array{ p3, p4 };
			if (is_cross(li, lj)) return 0;
		}
	}
	return 1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector x(k, 0), y(k, 0);
	for (int i = 0; i < k; i++) cin >> x[i] >> y[i];
	bool res = sol(n, m, k, x, y);
	cout << res << '\n';
}