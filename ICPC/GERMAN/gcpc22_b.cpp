#include <bits/stdc++.h>
using namespace std;

auto bipartite_matching = [](const auto& adj) { // 1-indexed
	const int n = adj.size() - 1;
	vector par(n + 1, 0), c(n + 1, 0);
	auto dfs = [&](const auto& self, int cur) -> bool {
		if (c[cur]++) return 0;
		for (int nxt : adj[cur]) {
			if (par[nxt] && !self(self, par[nxt])) continue;
			par[nxt] = cur;
			return 1;
		}
		return 0;
	};
	int res = 0;
	for (int i = 1; i <= n; i++) {
		fill(c.begin(), c.end(), 0);
		if (dfs(dfs, i)) res++;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int& x : v) cin >> x;
	sort(v.begin(), v.end());
	while (v.size() > 1 && v[1] == 1) v.erase(v.begin());
	n = v.size();

	bitset<20'000'000> b;
	for (int i = 2; i * i < b.size(); i++) {
		if (b[i]) continue;
		for (int j = i * i; j < b.size(); j += i) b[j] = 1;
	}

	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		if (b[v[i] + v[j]]) continue;
		int a = i + 1, b = j + 1;
		if (v[j] & 1) swap(a, b);
		adj[a].push_back(b);
	}
	cout << n - bipartite_matching(adj) << '\n';
}