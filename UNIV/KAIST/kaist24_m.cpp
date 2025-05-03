#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector sz(n + 1, 1), cnt(n + 1, 0);
	vector dp(n + 1, array{ 0LL, 0LL });
	auto pull = [&](int cur, int nxt, int d) {
		sz[cur] += d * sz[nxt];
		cnt[cur] += d * cnt[nxt];
		dp[cur][0] += d * (dp[nxt][0] + sz[nxt] - cnt[nxt]);
		dp[cur][1] += d * (dp[nxt][1] + cnt[nxt]);
	};
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		if (s[cur - 1] == 'B') cnt[cur]++;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			pull(cur, nxt, 1);
		}
	};
	dfs(dfs, 1, 0);

	auto rec = [&](const auto& self, int cur, int prv) -> i64 {
		i64 res = 1LL << 60;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			if (cnt[nxt] == (sz[cur] - sz[nxt]) - (cnt[cur] - cnt[nxt])) {
				i64 a = dp[nxt][1];
				i64 b = dp[cur][0] - (dp[nxt][0] + sz[nxt] - cnt[nxt]);
				res = min(res, a + b + cnt[nxt]);
			}
			if (sz[nxt] - cnt[nxt] == cnt[cur] - cnt[nxt]) {
				i64 a = dp[nxt][0];
				i64 b = dp[cur][1] - (dp[nxt][1] + cnt[nxt]);
				res = min(res, a + b + sz[nxt] - cnt[nxt]);
			}
			pull(cur, nxt, -1);
			pull(nxt, cur, 1);
			res = min(res, self(self, nxt, cur));
			pull(nxt, cur, -1);
			pull(cur, nxt, 1);
		}
		return res;
	};

	i64 res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) {
			if (sz[i] < sz[j]) continue;
			int a = cnt[1], b = sz[1] - cnt[1];
			int sa = cnt[j], sb = sz[j] - cnt[j];
			if (sa && a - sa) res++;
			if (sb && b - sb) res++;
		}
	}
	cout << min(res, rec(rec, 1, 0) + n - 2) << '\n';
}