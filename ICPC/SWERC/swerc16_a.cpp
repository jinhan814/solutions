#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	double x, y; cin >> x >> y;

	vector ran(n, pair(0, 0));
	ran[0] = pair(v[0], v[0]);
	for (int i = 1; i < n; i++) {
		auto [l, r] = ran[i - 1];
		if (v[i] <= l) ran[i] = pair(l - v[i], r + v[i]);
		else if (v[i] <= r) ran[i] = pair(0, r + v[i]);
		else ran[i] = pair(v[i] - r, r + v[i]);
	}

	auto get_dist = [](const auto& a, const auto& b) {
		double dx = a.first - b.first;
		double dy = a.second - b.second;
		return sqrt(dx * dx + dy * dy);
	};

	auto get_inter = [&](const auto& p, double r1, double r2) {
		double r3 = get_dist(pair(0, 0), p);
		double c = (r1 * r1 + r3 * r3 - r2 * r2) / (2 * r1 * r3);
		double s = sqrt(1 - c * c);
		double dx = p.first / r3;
		double dy = p.second / r3;
		double x = dx * r1 * c + dy * r1 * s;
		double y = dy * r1 * c - dx * r1 * s;
		return pair(x, y);
	};

	{
		auto d = get_dist(pair(0, 0), pair(x, y));
		auto [l, r] = ran[n - 1];
		if (d < l) x *= l / d, y *= l / d;
		if (d > r) x *= r / d, y *= r / d;
	}

	vector res(n, pair(0., 0.));
	res[n - 1] = pair(x, y);
	for (int i = n - 2; i >= 0; i--) {
		auto d = get_dist(pair(0, 0), res[i + 1]);
		auto [l, r] = ran[i];
		if (d + v[i + 1] > r) res[i] = get_inter(res[i + 1], r, v[i + 1]);
		else if (abs(d - v[i + 1]) < l) res[i] = get_inter(res[i + 1], l, v[i + 1]);
		else res[i] = pair(res[i + 1].first + v[i + 1], res[i + 1].second);
	}

	cout << fixed << setprecision(20);
	for (auto [x, y] : res) cout << x << ' ' << y << '\n';
}