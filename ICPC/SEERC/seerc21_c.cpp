#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }

auto sol = [](int n, const auto& v, const auto& adj) {
	vector sz(n + 1, 0), acc(n + 1, 0);
	vector dp(n + 1, vector(0, 0));
	auto dfs = [&](const auto& self, int cur, int prv, int x) -> void {
		sz[cur] = 1;
		acc[cur] = v[cur] == x;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur, x);
			sz[cur] += sz[nxt];
			acc[cur] += acc[nxt];
		}
	};
	auto merge = [&](const auto& dp_cur, const auto& dp_sub) {
		int sz_cur = dp_cur.size() >> 1;
		int sz_sub = dp_sub.size() >> 1;
		int sz_nxt = min(sz_cur + sz_sub, acc[1]);
		vector dp_nxt(2 * sz_nxt + 1, 0);
		for (int i = -sz_cur; i <= sz_cur; i++) {
			dp_nxt[sz_nxt + i] = add(dp_nxt[sz_nxt + i], dp_cur[sz_cur + i]);
			for (int j = -sz_sub; j <= sz_sub; j++) {
				if (abs(i + j) > sz_nxt) continue;
				int val = mul(dp_cur[sz_cur + i], dp_sub[sz_sub + j]);
				dp_nxt[sz_nxt + i + j] = add(dp_nxt[sz_nxt + i + j], val);
			}
		}
		return dp_nxt;
	};
	auto rec = [&](const auto& self, int cur, int prv, int x) -> void {
		vector dp_cur(3, 0); dp_cur[v[cur] == x ? 2 : 0]++;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur, x);
			dp_cur = merge(dp_cur, dp[nxt]);
		}
		dp[cur] = dp_cur;
	};
	int res = 0;
	for (int x = 1; x <= n; x++) {
		dfs(dfs, 1, 0, x);
		if (!acc[1]) continue;
		rec(rec, 1, 0, x);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < dp[i].size(); j++) {
				if (2 * j <= dp[i].size()) continue;
				res = add(res, dp[i][j]);
			}
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, v, adj) << '\n';
}