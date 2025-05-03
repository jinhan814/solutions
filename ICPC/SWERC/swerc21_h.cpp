#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(3, pair(0., 0.));
	for (auto& [a, b] : v) cin >> a >> b;

	auto ternary = [](const auto& f) {
		auto xl = -1e4, xr = 1e4;
		while (xr - xl > 1e-6) {
			auto l = (xl + xl + xr) / 3;
			auto r = (xl + xr + xr) / 3;
			if (f(l) > f(r)) xl = l;
			else xr = r;
		}
		return xl;
	};

	auto fermat = [&](auto a, auto b, auto c) {
		auto dist = [](auto a, auto b) { return hypot(a.first - b.first, a.second - b.second); };
		auto x = dist(a, b), y = dist(a, c), z = dist(b, c);
		if (x > y) swap(x, y);
		if (x > z) swap(x, z);
		if (y > z) swap(y, z);
		if (z * z > x * x + y * y + x * y) return x + y;
		auto s = (x + y + z) / 2;
		auto area = sqrt(s * (s - x) * (s - y) * (s - z));
		return sqrt((x * x + y * y + z * z + 4 * sqrt(3) * area) / 2);
	};

	auto sol = [&](auto a, auto b, auto c) {
		auto f = [&](auto x) {
			auto res1 = fermat(a, b, x);
			auto res2 = fermat(a, c, x);
			auto res3 = fermat(b, c, x);
			return max({ res1, res2, res3 });
		};
		auto g = [&](auto x) {
			return f(pair(x, ternary([&](auto y) { return f(pair(x, y)); })));
		};
		return g(ternary(g));
	};

	cout << fixed << setprecision(20);
	cout << sol(v[0], v[1], v[2]) << '\n';
}