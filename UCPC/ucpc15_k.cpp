#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2'000'000'000;

auto sol = [](int n, int m, auto adj) {
	auto check = [&](int x) {
		auto rec = [&](const auto& self, int cur, int prv) -> vector<int> {
			vector dp(1, 0);
			for (auto [nxt, cost] : adj[cur]) {
				if (nxt == prv) continue;
				vector val = self(self, nxt, cur);
				vector ndp(dp.size() + val.size(), inf);
				for (int i = 0; i < dp.size(); i++) {
					for (int j = 0; j < val.size(); j++) {
						ndp[i + j] = min(ndp[i + j], dp[i]);
						if (dp[i] + val[j] + cost > x) continue;
						ndp[i + j + 1] = min(ndp[i + j + 1], max(dp[i], val[j] + cost));
					}
				}
				dp.swap(ndp);
				while (dp.back() == inf) dp.pop_back();
			}
			return dp;
		};
		return rec(rec, 1, 0).size() > m;
	};
	int lo = 0, hi = inf;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (!check(mid)) lo = mid;
		else hi = mid;
	}
	return hi;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector adj(n + 1, vector(0, array{ 0, 0 }));
		for (int i = 1; i < n; i++) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back({ b, c });
			adj[b].push_back({ a, c });
		}
		cout << sol(n, m, adj) << '\n';
	}
}