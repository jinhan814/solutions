#include <bits/stdc++.h>
using namespace std;

constexpr int bias = 2'000'000;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;

	vector buc1(bias << 1 | 1, vector(0, pair(0, 0)));
	vector buc2(bias << 1 | 1, vector(0, pair(0, 0)));
	for (int i = 0; i < n; i++) {
		auto [x1, y1] = v[i];
		auto [x2, y2] = v[(i + 1) % n];
		int dx = x2 > x1 ? 1 : x2 < x1 ? -1 : 0;
		int dy = y2 > y1 ? 1 : y2 < y1 ? -1 : 0;
		while (x1 != x2 || y1 != y2) {
			x1 += dx, y1 += dy;
			buc1[x1 + y1 + bias].push_back({ x1, abs(dy) });
			buc2[x1 - y1 + bias].push_back({ x1, abs(dy) });
			x1 += dx, y1 += dy;
		}
	}
	for (auto& v : buc1) ranges::sort(v);
	for (auto& v : buc2) ranges::sort(v);

	int x, y, d = 0; cin >> x >> y;
	while (m--) {
		if (d == 0) {
			auto it = next(ranges::lower_bound(buc2[x - y + bias], pair(x, -1)));
			y = it->first - x + y;
			x = it->first;
			d = it->second ? 1 : 3;
		}
		else if (d == 2) {
			auto it = prev(ranges::lower_bound(buc2[x - y + bias], pair(x, -1)));
			y = it->first - x + y;
			x = it->first;
			d = it->second ? 3 : 1;
		}
		else if (d == 1) {
			auto it = prev(ranges::lower_bound(buc1[x + y + bias], pair(x, -1)));
			y = x + y - it->first;
			x = it->first;
			d = it->second ? 0 : 2;
		}
		else if (d == 3) {
			auto it = next(ranges::lower_bound(buc1[x + y + bias], pair(x, -1)));
			y = x + y - it->first;
			x = it->first;
			d = it->second ? 2 : 0;
		}
		cout << x << ' ' << y << '\n';
	}
}