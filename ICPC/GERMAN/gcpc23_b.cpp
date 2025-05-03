#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, pair(0, 0));
	for (auto& [x, y] : v) cin >> x >> y;

	auto ccw = [](const auto& a, const auto& b, const auto& c) {
		int x1 = b.first - a.first;
		int y1 = b.second - a.second;
		int x2 = c.first - b.first;
		int y2 = c.second - b.second;
		return 1LL * x1 * y2 - 1LL * x2 * y1;
	};

	auto dfs = [&](const auto& self, const auto& v, int k) -> bool {
		if (v.size() < k + 1) return 1;
		for (int i = 0; i <= k; i++) for (int j = i + 1; j <= k; j++) {
			vector res(0, pair(0, 0));
			for (const auto& p : v) if (ccw(v[i], v[j], p)) res.push_back(p);
			if (self(self, res, k - 1)) return 1;
		}
		return 0;
	};

	cout << (dfs(dfs, v, 3) ? "possible" : "impossible") << '\n';
}