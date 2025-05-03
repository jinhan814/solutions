#include <bits/stdc++.h>
using namespace std;

auto bipartite_matching = [](const auto& adj) {
	const int n = adj.size() - 1;
	vector par(n + 1, 0), c(n + 1, 0);
	auto dfs = [&](const auto& self, int cur) -> bool {
		if (c[cur]++) return 0;
		for (int nxt : adj[cur])
			if (!par[nxt] || self(self, par[nxt]))
				return par[nxt] = cur, 1;
		return 0;
	};
	int res = 0;
	for (int i = 1; i <= n; i++) {
		fill(c.begin(), c.end(), 0);
		if (dfs(dfs, i)) res++;
	}
	return res;
};

auto comp = [](const auto& v) {
	vector res(0, v[0]);
	for (const auto& x : v) {
		auto it = ranges::find(res, x);
		if (it == res.end()) res.push_back(x);
	}
	return res;
};

auto sol = [](int n, auto g) {
	vector v(0, bitset<1024>{});
	for (int i = 0; i < n; i++) {
		if (!g[i].any()) {
			auto a = g[i];
			a[i] = 1;
			v.push_back(a);
		}
		else {
			int j = 0;
			while (!g[i][j]) j++;
			auto a = g[i] & g[j];
			auto b = g[i] & ~a;
			a[i] = a[j] = b[i] = 1; b[j] = 0;
			v.push_back(a);
			v.push_back(b);
		}
	}
	v = comp(v);
	vector buc(n, vector(0, 0));
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (!v[i][j]) continue;
			buc[j].push_back(i + 1);
		}
	}
	vector adj(v.size() + 1, vector(0, 0));
	for (int i = 0; i < n; i++) {
		if (buc[i].empty()) continue;
		for (int a : buc[i]) for (int b : buc[i]) {
			if (a >= b) continue;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	int res = bipartite_matching(adj) >> 1;
	for (int i = 1; i <= v.size(); i++) {
		if (adj[i].size()) continue;
		res++;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector g(n, bitset<1024>{});
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < n; j++) g[i][j] = s[j] & 1;
	}
	cout << sol(n, g) << '\n';
}