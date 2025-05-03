#include <bits/stdc++.h>
using namespace std;

auto ccw = [](const auto& a, const auto& b, const auto& c) {
	int x1 = b.first - a.first;
	int y1 = b.second - a.second;
	int x2 = c.first - b.first;
	int y2 = c.second - b.second;
	return 1LL * x1 * y2 - 1LL * x2 * y1;
};

auto ext_gcd = [](const auto& self, int a, int b) {
	if (!b) return pair(1, 0);
	auto [y, x] = self(self, b, a % b);
	return pair(x, y - a / b * x);
};

auto sol = [](const auto& v) {
	vector res(0, pair(0LL, 0LL));
	vector buc(2, vector(0, pair(0, 0)));
	for (const auto& x : v) buc[x > pair(0, 0)].push_back(x);

	auto is_collinear = [&] {
		for (int i = 1; i < v.size(); i++) {
			auto res = ccw(pair(0, 0), v[0], v[i]);
			if (res) return 0;
		}
		return 1;
	};

	if (v.empty()) {
		return res;
	}
	if (is_collinear()) {
		if (buc[1].size()) swap(buc[0], buc[1]);
		auto [a, b] = buc[0][0];
		int g = gcd(a, b); a /= g, b /= g;
		res.push_back({ a, b });
		if (buc[1].size()) res.push_back({ -a, -b });
		return res;
	}

	auto is_half_plane = [&](auto p) {
		for (int i = 0; i < v.size(); i++) {
			auto res = ccw(pair(0, 0), p, v[i]);
			if (res < 0) return 0;
			if (res == 0 && pair(0, 0) < p ^ pair(0, 0) < v[i]) return 0;
		}
		return 1;
	};

	vector cand(0, pair(0, 0));
	for (const auto& t : buc) {
		if (t.empty()) continue;
		auto mn = t[0], mx = t[0];
		for (int i = 1; i < t.size(); i++) {
			if (ccw(pair(0, 0), mn, t[i]) < 0) mn = t[i];
			if (ccw(pair(0, 0), mx, t[i]) > 0) mx = t[i];
		}
		if (is_half_plane(mn)) cand.push_back(mn);
		if (is_half_plane(mx)) cand.push_back(mx);
	}

	if (cand.size()) {
		auto [a, b] = cand[0];
		int g = abs(gcd(a, b)); a /= g, b /= g;
		auto [x, y] = ext_gcd(ext_gcd, abs(a), abs(b));
		for (int i = 0; i < 4; i++) {
			if (1LL * a * x - 1LL * b * y == 1) break;
			x = -x;
			if (i & 1) y = -y;
		}
		res.push_back({ a, b });
		res.push_back({ y - (1LL << 30) * a, x - (1LL << 30) * b });
		return res;
	}
	else {
		res.push_back({ 1, 0 });
		res.push_back({ 0, 1 });
		res.push_back({ -1, -1 });
		return res;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(0, pair(0, 0));
		for (int i = 0; i < n; i++) {
			int a, b; cin >> a >> b;
			if (a || b) v.push_back({ a, b });
		}
		auto res = sol(v);
		cout << res.size() << '\n';
		for (auto [a, b] : res) cout << a << ' ' << b << '\n';
	}
}