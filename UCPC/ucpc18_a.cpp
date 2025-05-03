#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k, sx, sy, ex, ey;
	cin >> sx >> sy >> k >> ex >> ey >> n;
	int sz = 2 * k + 1;
	vector c(sz, vector(sz, 0));
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		if (abs(sx - x) + abs(sy - y) > k) continue;
		c[x - sx + k][y - sy + k] = 1;
	}
	int res = 0;
	vector dp(sz, vector(sz, 0)); dp[k][k] = 1;
	for (int iter = 0; iter < k; iter++) {
		vector ndp(sz, vector(sz, 0));
		auto add = [](int& a, int b) {
			a += b;
			if (a >= mod) a -= mod;
		};
		auto update = [&](int x, int y) {
			if (dp[x][y] == 0) return;
			for (int i = 0; i < 4; i++) {
				int nx = x + "1012"[i] - '1';
				int ny = y + "2101"[i] - '1';
				if (c[nx][ny]) continue;
				if (nx == ex - sx + k && ny == ey - sy + k) add(res, dp[x][y]);
				else add(ndp[nx][ny], dp[x][y]);
			}
		};
		for (int i = 0; i < sz * sz; i++) update(i / sz, i % sz);
		dp.swap(ndp);
	}
	cout << res << '\n';
}