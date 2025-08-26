#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(n, vector(n, 0LL));
	vector pl(n, vector(n, 0LL));
	vector pr(n, vector(n, 0LL));
	vector opt(n, 0);
	for (int i = 0; i < n; i++) opt[i] = i + 1;
	for (int sz = 1; sz <= n; sz++) {
		for (int l = 0; l + sz - 1 < n; l++) {
			int r = l + sz - 1;
			dp[l][r] = max(v[l], v[r]);
			if (sz <= 2) continue;
			while (opt[l] < r && dp[l][opt[l] - 1] <= dp[opt[l] + 1][r]) opt[l]++;
			if (opt[l] - 2 >= l) dp[l][r] = max(dp[l][r], pl[l][opt[l] - 2]);
			if (opt[l] + 1 <= r) dp[l][r] = max(dp[l][r], pr[opt[l] + 1][r]);
		}
		for (int l = 0; l + sz - 1 < n; l++) {
			int r = l + sz - 1;
			if (r) pl[l][r] = pl[l][r - 1];
			if (l + 1 < n) pr[l][r] = pr[l + 1][r];
			if (r + 1 < n) pl[l][r] = max(pl[l][r], dp[l][r] + v[r + 1]);
			if (l) pr[l][r] = max(pr[l][r], dp[l][r] + v[l - 1]);
		}
	}
	return dp[0][n - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}