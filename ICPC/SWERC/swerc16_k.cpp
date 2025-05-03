#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array<int, 6>{});
	for (int i = 0; i < n; i++) for (int j = 0; j < 6; j++) cin >> v[i][j];

	auto sol = [&](const auto& adj) -> bool {
		const int n = adj.size();
		vector c(n, 0);
		int ord = 0;
		auto dfs = [&](const auto& self, int cur, int prv) -> bool {
			c[cur] = ++ord;
			for (int nxt : adj[cur]) if (nxt != prv) {
				if (!c[nxt] && self(self, nxt, cur)) return 1;
				if (c[nxt] < c[cur]) return 1;
			}
			return 0;
		};
		for (int i = 0; i < n; i++) if (!c[i] && dfs(dfs, i, -1)) return 1;
		return 0;
	};

	auto sol_3d = [&]() -> bool {
		map<array<int, 3>, int> m;
		for (int i = 0; i < n; i++) {
			array<int, 3> a{ v[i][0], v[i][1], v[i][2] };
			array<int, 3> b{ v[i][3], v[i][4], v[i][5] };
			if (m.count(a) == 0) m[a] = m.size();
			if (m.count(b) == 0) m[b] = m.size();
		}
		vector adj(m.size(), vector(0, 0));
		for (int i = 0; i < n; i++) {
			array<int, 3> a{ v[i][0], v[i][1], v[i][2] };
			array<int, 3> b{ v[i][3], v[i][4], v[i][5] };
			adj[m[a]].push_back(m[b]);
			adj[m[b]].push_back(m[a]);
		}
		return sol(adj);
	};

	auto sol_2d = [&]() -> bool {
		map<array<int, 2>, int> m;
		for (int i = 0; i < n; i++) {
			array<int, 2> a{ v[i][0], v[i][1] };
			array<int, 2> b{ v[i][3], v[i][4] };
			if (m.count(a) == 0) m[a] = m.size();
			if (m.count(b) == 0) m[b] = m.size();
		}
		vector adj(m.size(), vector(0, 0));
		for (int i = 0; i < n; i++) {
			array<int, 2> a{ v[i][0], v[i][1] };
			array<int, 2> b{ v[i][3], v[i][4] };
			adj[m[a]].push_back(m[b]);
			adj[m[b]].push_back(m[a]);
		}
		return sol(adj);
	};

	if (sol_3d()) cout << "True closed chains" << '\n';
	else cout << "No true closed chains" << '\n';
	if (sol_2d()) cout << "Floor closed chains" << '\n';
	else cout << "No floor closed chains" << '\n';
}