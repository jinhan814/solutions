#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	bitset<51> b;
	for (int i = 0; i < 2 * k; i++) { int x; cin >> x; b[x].flip(); }

	vector dp(n + 1, vector(n + 1, vector(n + 1, -1.)));
	vector bino(n + 1, vector(n + 1, 0.));
	for (int i = 0; i <= n; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++) bino[i][j] = bino[i - 1][j - 1] + bino[i - 1][j];
	}

	auto dfs = [&](const auto& self, int a, int b, int c) -> double {
		if (a < b) swap(a, b);
		if (b + c == 0) return 0;
		double& ret = dp[a][b][c];
		if (ret != -1.) return ret; ret = 0;
		for (int k = 0; k <= c && k <= m; k++) {
			for (int i = 0; i <= a && i + k <= m; i++) {
				for (int j = 0; j <= b && i + j + k <= m; j++) {
					if (!(i | j | k)) continue;
					double p = bino[a][i] * bino[b][j] * bino[c][k] * bino[n - a - b - c][m - i - j - k] / bino[n][m];
					ret += p * (self(self, a - i, b - j, c - k) + 1);
				}
			}
		}
		double p = bino[n - a - b - c][m] / bino[n][m];
		ret = (ret + p) / (1 - p);
		return ret;
	};

	int c = 2 * k - b.count() >> 1;
	cout << fixed << setprecision(20);
	cout << dfs(dfs, k - c, k - c, c) << '\n';
}