#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector x(n, pair(0, 0));
	vector y(n, pair(0, 0));
	for (int i = 0; i < n; i++) {
		cin >> x[i].second >> y[i].second;
		cin >> x[i].first >> y[i].first;
	}

	auto get_upper_hull = [&](auto v) {
		sort(v.begin(), v.end());
		vector res(0, pair(0, 0));
		for (auto x : v) {
			if (res.size() && res.back().first == x.first) res.pop_back();
			while (res.size() >= 2) {
				auto& a = res.end()[-2];
				auto& b = res.back();
				auto t1 = 1LL * (a.second - b.second) * (b.first - x.first);
				auto t2 = 1LL * (a.first - b.first) * (b.second - x.second);
				if (t1 > t2) break;
				res.pop_back();
			}
			res.push_back(x);
		}
		return res;
	};

	auto get_lower_hull = [&](auto v) {
		for (auto& [a, b] : v) a = -a, b = -b;
		auto res = get_upper_hull(v);
		return res;
	};

	auto x_hi = get_upper_hull(x);
	auto x_lo = get_lower_hull(x);
	auto y_hi = get_upper_hull(y);
	auto y_lo = get_lower_hull(y);

	auto get = [](const auto& v, double x) {
		int lo = 0, hi = v.size();
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			int a = v[mid].first - v[mid - 1].first;
			int b = v[mid].second - v[mid - 1].second;
			if (-b < x * a) lo = mid;
			else hi = mid;
		}
		return v[lo].first * x + v[lo].second;
	};

	auto f = [&](const auto& v) {
		vector buc(1, 0.);
		for (int i = 1; i < v.size(); i++) {
			int a = v[i].first - v[i - 1].first;
			int b = v[i].second - v[i - 1].second;
			if (b < 0) buc.push_back(-1. * b / a);
		}
		double res = 1e20;
		for (auto x : buc) {
			auto dx = get(x_hi, x) + get(x_lo, x);
			auto dy = get(y_hi, x) + get(y_lo, x);
			res = min(res, dx * dy);
		}
		return res;
	};

	double res = min({ f(x_hi), f(x_lo), f(y_hi), f(y_lo) });
	cout << fixed << setprecision(20);
	cout << res << '\n';
}