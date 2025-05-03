#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector dp(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1] + a[i][1];
		for (int j = 1; j <= m; j++) {
			int lo = 0, hi = i;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				if (a[mid][0] < a[i][0] - b[j][0] + 1) lo = mid;
				else hi = mid;
			}
			int p = max(lo, i - b[j][1]);
			dp[i] = min(dp[i], dp[p] + b[j][2]);
		}
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n + 1, array{ 0, 0 });
	vector b(m + 1, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
	for (int i = 1; i <= m; i++) cin >> b[i][0] >> b[i][1] >> b[i][2];
	cout << sol(n, m, a, b) << '\n';
}