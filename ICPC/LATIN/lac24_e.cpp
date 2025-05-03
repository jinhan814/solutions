#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector in(n + 1, 0);
	vector out(n + 1, 0);
	for (int i = 1; i <= 2 * n; i++) {
		int x; cin >> x;
		if (x > 0) in[x] = i;
		else out[-x] = i;
	}

	auto sol = [&]() -> string {
		if (n == 1) return "G";
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (in[i] < in[j] && in[j] < out[i] && out[i] < out[j] ||
					in[j] < in[i] && in[i] < out[j] && out[j] < out[i]) adj[i].push_back(j);
			}
		}
		vector c(n + 1, 0);
		auto dfs = [&](const auto& self, int cur, int col) -> bool {
			c[cur] = col;
			for (int nxt : adj[cur]) {
				if (!c[nxt] && !self(self, nxt, col ^ 3)) return 0;
				if (c[nxt] == col) return 0;
			}
			return 1;
		};
		for (int i = 1; i <= n; i++) {
			if (c[i]) continue;
			if (!dfs(dfs, i, 1)) return "*";
		}
		string res;
		for (int i = 1; i <= n; i++) res.push_back("GS"[c[i] - 1]);
		return res;
	};

	cout << sol() << '\n';
}