#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> v[i][j];

	auto calc = [&](int i, int j) -> int {
		vector c(n, string(m, 0));
		auto dfs = [&](const auto& self, int x, int y) -> int {
			int ret = c[x][y] = 1;
			for (int d = 0; d < 4; d++) {
				int nx = x + "1012"[d] - '1';
				int ny = y + "2101"[d] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (c[nx][ny]) continue;
				if (v[nx][ny] > v[x][y]) ret += self(self, nx, ny);
			}
			return ret;
		};
		return dfs(dfs, i, j);
	};

	int res = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		int cnt = 0;
		for (int d = 0; d < 4; d++) {
			int nx = i + "1012"[d] - '1';
			int ny = j + "2101"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (v[nx][ny] < v[i][j]) cnt++;
		}
		if (!cnt) res = max(res, calc(i, j));
	}
	cout << res << '\n';
}