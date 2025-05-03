#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector a(21, vector(360, 0));
		vector b(21, vector(360, 0));
		for (int i = 0; i < n; i++) {
			char c; cin >> c;
			if (c == 'C') {
				int p, l, r; cin >> p >> l >> r;
				while (l % 360 != r) a[p][l++ % 360] = 1;
			}
			else {
				int p, l, r; cin >> l >> r >> p;
				while (l != r) b[l++][p] = 1;
			}
		}

		vector c(21, vector(360, 0));
		auto dfs = [&](const auto& self, int x, int y) -> bool {
			if (x == 20) return 1;
			for (int d = 0; d < 4; d++) {
				int nx = x + "1012"[d] - '1';
				int ny = y + "2101"[d] - '1';
				if (nx < 0 || nx > 20) continue;
				if (ny < 0) ny += 360;
				if (ny >= 360) ny -= 360;
				if (x != nx && a[d & 2 ? nx : x][y]) continue;
				if (y != ny && b[x][d & 2 ? y : ny]) continue;
				if (!c[nx][ny]++ && self(self, nx, ny)) return 1;
			}
			return 0;
		};
		cout << (dfs(dfs, 0, 0) ? "YES" : "NO") << '\n';
	}
}