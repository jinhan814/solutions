#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	f64 xl = v[0][0], xr = v[n - 1][0];
	auto f = [&](f64 a, f64 b) {
		f64 mx = -1e100, mn = 1e100;
		for (auto [x, y] : v) {
			f64 val = a * (x - xl) * (x - xr) + b * (x - xl);
			mx = max(mx, val - y);
			mn = min(mn, val - y);
		}
		return (mx - mn) / 2;
	};
	auto g = [&](f64 a) {
		f64 lo = -1e7, hi = 1e7;
		for (int iter = 0; iter < 200; iter++) {
			f64 l = (lo + lo + hi) / 3;
			f64 r = (lo + hi + hi) / 3;
			if (f(a, l) >= f(a, r)) lo = l;
			else hi = r;
		}
		return f(a, (lo + hi) / 2);
	};
	f64 lo = -1e7, hi = 1e7;
	for (int iter = 0; iter < 200; iter++) {
		f64 l = (lo + lo + hi) / 3;
		f64 r = (lo + hi + hi) / 3;
		if (g(l) >= g(r)) lo = l;
		else hi = r;
	}
	f64 val = g((lo + hi) / 2);
	return val * val;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(20);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}