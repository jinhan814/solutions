#include <bits/stdc++.h>
using namespace std;

auto ccw = [](auto a, auto b, auto c) {
	int x1 = b.first - a.first;
	int y1 = b.second - a.second;
	int x2 = c.first - b.first;
	int y2 = c.second - b.second;
	return 1LL * x1 * y2 - 1LL * x2 * y1;
};

auto conv = [](auto a, auto b) { 
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	int g = gcd(abs(dx), abs(dy));
	vector res(0, pair(0, 0));
	if (g > 1) {
		res.push_back({ a.first + dx / g, a.second + dy / g });
		res.push_back({ b.first - dx / g, b.second - dy / g });
	}
	return res;
};

auto sol = [](auto v) {
	vector buc(3, vector(0, pair(0, 0)));
	buc[0] = conv(v[0], v[1]);
	buc[1] = conv(v[0], v[2]);
	buc[2] = conv(v[1], v[2]);
	auto mx = -1LL, mn = 1LL << 60;
	for (auto a : buc[0]) for (auto b : buc[1]) for (auto c : buc[2]) {
		auto val = abs(ccw(a, b, c));
		mx = max(mx, val);
		mn = min(mn, val);
	}
	return pair(mx, mn);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(3, pair(0, 0));
	for (auto& [x, y] : v) cin >> x >> y;
	auto [a, b] = sol(v);
	if (a == -1) cout << -1 << '\n';
	else cout << a << ' ' << b << '\n';
}