#include <bits/stdc++.h>
using namespace std;

auto f = [](int& a, int b) { if (a < b) a = b; };

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, vector(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cin >> v[i][j];
	}
	vector res(n + 1, vector(m + 1, -(1 << 30)));
	for (int r = n; r >= 1; r--) {
		vector p(m + 1, 0), dp(m + 1, 0);
		for (int l = r; l >= 1; l--) {
			for (int i = 1; i <= m; i++) {
				p[i] += v[l][i];
				dp[i] = max(dp[i - 1], 0) + p[i];
			}
			for (int i = m, x = 0; i >= 1; i--) {
				x = max(x, 0) + p[i];
				f(res[l][i], dp[i] + x - p[i]);
			}
		}
		for (int l = 1; l < r; l++) {
			for (int i = 1; i <= m; i++) {
				f(res[l + 1][i], res[l][i]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
}