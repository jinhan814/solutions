#include <bits/stdc++.h>
using namespace std;

auto ccw = [](const auto& a, const auto& b, const auto& c) {
	int x1 = b.first - a.first;
	int y1 = b.second - a.second;
	int x2 = c.first - b.first;
	int y2 = c.second - b.second;
	return 1LL * x1 * y2 - 1LL * x2 * y1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, pair(0, 0)), qu(q, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;
	for (auto& [a, b] : qu) cin >> a >> b;
	
	int x = 0;
	auto f = [](auto p) { return p.first > 0 || p.first == 0 && p.second > 0; };
	while (f(v[x])) x++;
	while (x < n && !f(v[x])) x++;
	rotate(v.begin(), v.begin() + x, v.end()); x = 0;
	while (f(v[x])) x++;

	auto is_in = [&](const auto& p) -> bool {
		if (p == pair(0, 0)) return 1;
		if (ccw(pair(0, 0), v[x - 1], p) > 0 &&
			ccw(pair(0, 0), v[x], p) < 0) {
			return ccw(v[x - 1], v[x], p) >= 0;
		}
		if (ccw(pair(0, 0), v[n - 1], p) > 0 &&
			ccw(pair(0, 0), v[0], p) < 0) {
			return ccw(v[n - 1], v[0], p) >= 0;
		}
		auto [lo, hi] = f(p) ? pair(0, x) : pair(x, n);
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (ccw(pair(0, 0), v[mid], p) >= 0) lo = mid;
			else hi = mid;
		}
		if (lo && ccw(v[lo - 1], v[lo], p) == 0) {
			auto a = v[lo - 1], b = v[lo];
			if (a > b) swap(a, b);
			return p <= b;
		}
		return ccw(v[lo], v[hi], p) >= 0;
	};

	auto move = [&](const auto& a, const auto& b, bool f) {
		const auto& [px, py] = a;
		const auto& [cx, cy] = b;
		if (f) return pair(2 * cx - px, 2 * cy - py);
		return pair((cx + px) / 2, (cy + py) / 2);
	};

	int res = is_in(qu[0]);
	cout << res << '\n';
	for (int i = 1; i < q; i++) {
		qu[i] = move(qu[i - 1], qu[i], res);
		res = is_in(qu[i]);
		cout << res << '\n';
	}
}