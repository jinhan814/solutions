#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	auto check = [&](int lim) -> bool {
		auto dfs = [&](const auto& self, int cur, int prv, int dep) -> int {
			if (dep > lim) return 0;
			int ret = v[cur];
			for (int nxt : adj[cur]) if (nxt != prv) ret += self(self, nxt, cur, dep + 1);
			return ret;
		};
		if (lim & 1) {
			lim /= 2;
			for (int i = 1; i <= n; i++) for (int j : adj[i]) {
				if (i > j) continue;
				int res = dfs(dfs, i, j, 0) + dfs(dfs, j, i, 0);
				if (res >= m) return 1;
			}
			return 0;
		}
		else {
			lim /= 2;
			for (int i = 1; i <= n; i++) {
				int res = dfs(dfs, i, -1, 0);
				if (res >= m) return 1;
			}
			return 0;
		}
	};

	int lo = -1, hi = n;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (!check(mid)) lo = mid;
		else hi = mid;
	}
	cout << hi << '\n';
}