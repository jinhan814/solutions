#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, q; cin >> n >> q;
	vector v(n, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;
	vector qu(q, pair(0, 0));
	for (auto& [a, b] : qu) cin >> a >> b;

	int x = 0;
	auto f = [](auto p) { return p.first > 0 || p.first == 0 && p.second > 0; };
	while (f(v[x])) x++;
	while (x < n && !f(v[x])) x++;
	rotate(v.begin(), v.begin() + x, v.end()); x = 0;
	while (f(v[x])) x++;

	auto ccw = [](const auto& a, const auto& b, const auto& c) {
		int x1 = b.first - a.first;
		int y1 = b.second - a.second;
		int x2 = c.first - b.first;
		int y2 = c.second - b.second;
		return 1LL * x1 * y2 - 1LL * x2 * y1;
	};

	auto is_in_triangle = [&](const auto& a, const auto& b, const auto& c, const auto& p) -> bool {
		if (ccw(a, b, p) < 0) return 0;
		if (ccw(b, c, p) < 0) return 0;
		if (ccw(c, a, p) < 0) return 0;
		return 1;
	};

	auto is_in = [&](const auto& p) -> bool {
		if (p == pair(0, 0)) return 1;
		if (ccw(pair(0, 0), v[x - 1], p) >= 0 &&
			ccw(pair(0, 0), v[x], p) <= 0) {
			return is_in_triangle(pair(0, 0), v[x - 1], v[x], p);
		}
		if (ccw(pair(0, 0), v[n - 1], p) >= 0 &&
			ccw(pair(0, 0), v[0], p) <= 0) {
			return is_in_triangle(pair(0, 0), v[n - 1], v[0], p);
		}
		auto [lo, hi] = p.first > 0 ? pair(0, x - 1) : pair(x - 1, n - 1);
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (ccw(pair(0, 0), v[mid], p) >= 0) lo = mid;
			else hi = mid;
		}
		return is_in_triangle(pair(0, 0), v[lo], v[hi], p);
	};

	auto move = [&](const auto& a, const auto& b, bool f) {
		const auto& [px, py] = a;
		const auto& [cx, cy] = b;
		if (f) return pair(2 * cx - px, 2 * cy - py);
		return pair((cx + px) / 2, (cy + py) / 2);
	};

	vector res(q, 0);
	res[0] = is_in(qu[0]);
	for (int i = 1; i < q; i++) {
		qu[i] = move(qu[i - 1], qu[i], res[i - 1]);
		res[i] = is_in(qu[i]);
	}
	for (int x : res) cout << x << '\n';
}