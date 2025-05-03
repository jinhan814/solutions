#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector g(n + 1, bitset<1024>{});
	for (int i = 1; i <= n; i++) g[i].set();
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		g[a][b] = g[b][a] = 0;
	}

	vector c(n + 1, 0), cnt(3, 0);
	auto dfs = [&](const auto& self, int cur, int mask) -> bool {
		c[cur] = mask;
		cnt[mask]++;
		for (int nxt = 1; nxt <= n; nxt++) {
			if (nxt == cur || !g[cur][nxt]) continue;
			if (c[nxt] == mask) return 0;
			if (!c[nxt] && !self(self, nxt, mask ^ 3)) return 0;
		}
		return 1;
	};

	vector buc(0, pair(0, 0));
	for (int i = 1; i <= n; i++) {
		if (c[i]) continue;
		cnt[1] = cnt[2] = 0;
		if (!dfs(dfs, i, 1)) { buc.clear(); break; }
		buc.push_back({ cnt[1], cnt[2] });
	}

	if (buc.empty()) {
		cout << -1 << '\n';
		return 0;
	}

	bitset<1024> s; s[0] = 1;
	for (auto [a, b] : buc) s = s << a | s << b;
	int res = 1 << 30;
	for (int i = 0; 2 * i <= n; i++) if (s[i]) res = min(res, n - 2 * i);
	cout << res << '\n';
}