#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, const auto& adj) {
	int mx = 0, p = 1;
	for (int i = 1; i <= n; i++) {
		mx = max(mx, (int)adj[i].size());
		if (adj[p].size() > adj[i].size()) p = i;
	}
	vector v(n + 1, 0);
	auto rec = [&](const auto& self, int cur) -> void {
		v[cur] = 1 << 30;
		set s{ 0 };
		for (int nxt : adj[cur]) {
			if (!v[nxt]) self(self, nxt);
			s.insert(v[nxt]);
		}
		v[cur] = 0;
		while (s.count(++v[cur]));
	};
	rec(rec, p);
	return pair(mx, v);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto [c, v] = sol(n, m, adj);
	cout << (c | 1) << '\n';
	for (int i = 1; i <= n; i++) cout << v[i] << '\n';
}