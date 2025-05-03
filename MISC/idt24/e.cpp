#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto& v, const auto& queries) {
	const int n = v.size() - 1;
	const int q = queries.size();
	map buc{ pair(0, 0) };
	vector idx(n + 1, vector(0, 0));

	auto build = [&]() {
		for (auto [a, b] : buc) v[a] = b;
		buc.clear();
		for (int i = 1; i <= n; i++) idx[i].clear();
		for (int i = 1; i <= n; i++) idx[v[i]].push_back(i);
	};

	auto query = [&](int l, int r, int x) {
		auto lo = lower_bound(idx[x].begin(), idx[x].end(), l);
		auto hi = upper_bound(idx[x].begin(), idx[x].end(), r);
		int res = hi - lo;
		for (auto [a, b] : buc) {
			if (a < l || r < a) continue;
			if (v[a] == x && b != x) res--;
			if (v[a] != x && b == x) res++;
		}
		return res;
	};

	vector res(0, 0);
	for (int i = 0; i < q; i++) {
		if (i % 400 == 0) build();
		const auto& [t, a, b, c] = queries[i];
		if (t == 1) buc[a] = b;
		else res.push_back(query(a, b, c));
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, q; cin >> n >> q;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		vector in(n + 1, 0), out(n + 1, 0);
		int ord = 0;
		auto dfs = [&](const auto& self, int cur) -> void {
			in[cur] = ++ord;
			for (int nxt : adj[cur]) if (!in[nxt]) self(self, nxt);
			out[cur] = ord;
		};
		dfs(dfs, 1);

		vector nv(n + 1, 0);
		for (int i = 1; i <= n; i++) nv[in[i]] = v[i];

		vector queries(0, tuple(0, 0, 0, 0));
		for (int i = 0; i < q; i++) {
			int t, a, b; cin >> t >> a >> b;
			if (t == 1) queries.push_back({ 1, in[a], b, 0 });
			else queries.push_back({ 2, in[a], out[a], b });
		}

		auto res = sol(nv, queries);
		for (int x : res) cout << x << '\n';
	}
}