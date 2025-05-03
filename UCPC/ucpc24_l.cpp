#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(n, 0));
	vector idx(n * n, 0);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		cin >> v[i][j];
		idx[v[i][j] - 1] = i * n + j + 1;
	}

	vector adj(n * n + 1, vector(0, 0));
	vector par(n * n + 1, 0);
	auto match = [&](int i) {
		vector c(n * n + 1, 0);
		auto dfs = [&](const auto& self, int cur) -> bool {
			if (c[cur]++) return 0;
			for (int nxt : adj[cur]) {
				if (!par[nxt] || self(self, par[nxt]))
					return par[nxt] = cur, par[cur] = nxt, 1;
			}
			return 0;
		};
		return dfs(dfs, i);
	};

	for (int i : idx) {
		int x = (i - 1) / n, y = (i - 1) % n;
		for (int d = 0; d < 4; d++) {
			int nx = x + "1012"[d] - '1';
			int ny = y + "2101"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (v[nx][ny] > v[x][y]) continue;
			int j = nx * n + ny + 1;
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
		if (match(i)) cout << v[x][y] << '\n';
	}
}