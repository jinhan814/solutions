#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	int x = 1;
	while (adj[x].size() != 1) x++;
	vector dp(n + 1, 1 << 30);
	auto rec = [&](const auto& self, int cur) -> void {
		if (adj[cur].empty()) dp[cur] = cur;
		for (int nxt : adj[cur]) {
			adj[nxt].erase(ranges::find(adj[nxt], cur));
			self(self, nxt);
			dp[cur] = min(dp[cur], dp[nxt]);
		}
		sort(adj[cur].begin(), adj[cur].end(), [&](int i, int j) {
			return dp[i] < dp[j];
		});
	};
	rec(rec, x);
	vector res(0, 0);
	auto dfs = [&](const auto& self, int cur) -> void {
		for (int nxt : adj[cur]) self(self, nxt);
		res.push_back(cur);
	};
	while (res.size() < n) {
		for (int i = 0; i + 1 < adj[x].size(); i++) dfs(dfs, adj[x][i]);
		int nx = adj[x].size() ? adj[x].back() : -1;
		if (nx != -1 && x > dp[nx]) dfs(dfs, nx);
		res.push_back(x);
		x = nx;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		auto res = sol(n, adj);
		for (int x : res) cout << x << ' ';
		cout << '\n';
	}
}