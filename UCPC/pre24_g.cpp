#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	vector c(n, vector(m, string(8, 0)));
	auto rec = [&](const auto& self, int x, int y, int k) -> void {
		if (x < 0 || x >= n || y < 0 || y >= m) return;
		if (c[x][y][k]++) return;
		self(self, x, y, k ^ 1 << string("HIO").find(v[x][y]));
		self(self, x, y + (k & 1 ? 1 : -1), k ^ 1);
		self(self, x + (k & 2 ? 1 : -1), y, k ^ 2);
	};
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 8; k++) {
				if (c[i][j][k]) continue;
				rec(rec, i, j, k);
				res++;
			}
		}
	}
	cout << res << '\n';
}