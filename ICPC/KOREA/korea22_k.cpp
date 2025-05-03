#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector a(n, string{});
	vector b(m, string{});
	vector c(k, string{});
	for (auto& s : a) cin >> s;
	for (auto& s : b) cin >> s;
	for (auto& s : c) cin >> s;

	vector dp(n, vector(m + 1, vector(k + 1, -1)));
	auto dfs = [&](const auto& self, int i, int x, int y) -> int {
		if (i == n) return 0;
		int& ret = dp[i][x][y];
		if (ret != -1) return ret;
		ret = self(self, i + 1, x, y);
		if (x < m && a[i] == b[x]) ret = max(ret, self(self, i + 1, x + 1, y) + 1);
		if (y < k && a[i] == c[y]) ret = max(ret, self(self, i + 1, x, y + 1) + 1);
		if (x < m) ret = max(ret, self(self, i, x + 1, y));
		if (y < k) ret = max(ret, self(self, i, x, y + 1));
		return ret;
	};

	int res = dfs(dfs, 0, 0, 0);
	cout << res << '\n';
}