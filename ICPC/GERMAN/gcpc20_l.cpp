#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	vector dp(n, vector(m, 1 << 30));
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i - 1][j] == v[i][j]) continue;
			dp[i][j] = j;
		}
		for (int j = m - 2; j >= 0; j--) {
			dp[i][j] = min(dp[i][j], dp[i][j + 1]);
		}
	}

	auto get_opt = [&](int s) {
		int p = s;
		for (int i = 1; i < n; i++) {
			int j = dp[i][s];
			if (j <= p && v[i - 1][j] > v[i][j]) return 1 << 30;
			if (j <= p) continue;
			p = j;
			if (p >= m || v[i - 1][p] > v[i][p]) return 1 << 30;
		}
		return p;
	};

	int l = 0, r = 1 << 30;
	for (int i = 0; i < m; i++) {
		int p = get_opt(i);
		if (r - l > p - i) l = i, r = p;
	}
	cout << l + 1 << ' ' << r + 1 << '\n';
}