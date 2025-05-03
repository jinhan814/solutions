#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	map adj{ pair(string{}, vector(0, pair(string{}, 0.))) };
	for (int i = 0; i < n; i++) {
		double x; string s, t;
		cin >> x >> s >> t >> x >> t;
		adj[s].push_back({ t, x });
		adj[t].push_back({ s, 1 / x });
	}
	auto rec = [&](const auto& self, string s, string p, string t) -> double {
		if (s == t) return 1;
		for (auto [nxt, cost] : adj[s]) {
			if (nxt == p) continue;
			double res = self(self, nxt, s, t);
			if (res > 0) return cost * res;
		}
		return -1;
	};
	cout << setprecision(10);
	while (q--) {
		double x; cin >> x;
		string s, t; cin >> s >> t >> t;
		double res = rec(rec, s, "", t);
		if (res > 0) cout << x * res << '\n';
		else cout << "impossible" << '\n';
	}
}