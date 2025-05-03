#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b, c, d; cin >> n >> a >> b >> c >> d;
	bitset<1 << 19> v;
	auto dfs = [&](const auto& self, int x, int y, int s) -> void {
		if (x < 0 || x >= n || y < 0 || y >= n) return;
		if (v[x << 9 | y | s << 18]) return;
		v[x << 9 | y | s << 18] = 1;
		for (int i = 0; i < 4; i++) {
			int dx = ("0022"[i] - '1') * (s ? a : c);
			int dy = ("0202"[i] - '1') * (s ? b : d);
			self(self, x + dx, y + dy, !s);
			self(self, x + dy, y + dx, !s);
		}
	};
	dfs(dfs, 0, 0, 0);
	dfs(dfs, 0, 0, 1);
	cout << ((v | v >> (1 << 18)) & ~(v >> (1 << 18) << (1 << 18))).count() << '\n';
}