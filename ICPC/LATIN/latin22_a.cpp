#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector e(n + 1, pair(0, 0));
	for (int i = 1; i <= n; i++) {
		auto& [a, b] = e[i];
		cin >> a >> b;
	}

	auto sol = [&](int x) -> bool {
		vector rev(n + 1, vector(0, 0));
		for (int i = 1; i <= n; i++) {
			if (i == x) continue;
			auto [a, b] = e[i];
			rev[a].push_back(i);
			rev[b].push_back(i);
		}

		vector c(n + 1, 0);
		auto dfs = [&](const auto& self, int cur, int mask) -> void {
			c[cur] |= mask;
			for (int nxt : rev[cur]) if (~c[nxt] & mask) self(self, nxt, mask);
		};

		auto [a, b] = e[x];
		dfs(dfs, a, 1);
		dfs(dfs, b, 2);
		dfs(dfs, x, 4);
		return ranges::find(c, 7) != c.end();
	};

	string res;
	for (int i = 1; i <= n; i++) res.push_back("NY"[sol(i)]);
	cout << res << '\n';
}