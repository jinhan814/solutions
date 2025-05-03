#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, pair(0., 0.));
	for (auto& [a, b] : v) cin >> a >> b;

	auto dist = [](auto a, auto b, auto ang) {
		auto x = b.first - a.first;
		auto y = b.second - a.second;
		auto xp = ang.first * x + ang.second * y;
		auto yp = -ang.second * x + ang.first * y;
		return abs(xp) + abs(yp);
	};

	auto tsp = [&](const auto ang) {
		vector dp(1 << n, vector(n, -1.));
		auto dfs = [&](const auto& self, int s, int c) -> double {
			if (s + 1 >> n) return 0.;
			auto& res = dp[s][c];
			if (res != -1.) return res; res = 1e9;
			for (int i = 0; i < n; i++) {
				if (s >> i & 1) continue;
				res = min(res, self(self, s | 1 << i, i) + dist(v[c], v[i], ang));
			}
			return res;
		};
		auto res = 1e9;
		for (int i = 0; i < n; i++) res = min(res, dfs(dfs, 1 << i, i));
		return res;
	};

	auto res = 1e9;
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		auto [x1, y1] = v[i];
		auto [x2, y2] = v[j];
		auto l = hypot(x2 - x1, y2 - y1);
		auto ang = pair((x2 - x1) / l, (y2 - y1) / l);
		res = min(res, tsp(ang));
	}
	cout << fixed << setprecision(20) << res << '\n';
}