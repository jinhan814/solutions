#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	auto calc = [&](int x) {
		vector d(n + 1, -1), q(0, 0);
		d[x] = 0, q.push_back(x);
		while (q.size()) {
			auto cur = q.back(); q.pop_back();
			for (int nxt : adj[cur]) {
				if (d[nxt] != -1) continue;
				d[nxt] = d[cur] + 1, q.push_back(nxt);
			}
		}
		return d;
	};

	auto get = [&](const auto& f) {
		int p = 0;
		for (int i = 1; i <= n; i++) if (f(p) < f(i)) p = i;
		return calc(p);
	};

	auto dx = get([d1 = calc(1)](int i) { return d1[i]; });
	auto dy = get([&](int i) { return dx[i]; });
	auto dz = get([&](int i) { return dx[i] + dy[i]; });

	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		int res = max({ dx[a] + dx[b], dy[a] + dy[b], dz[a] + dz[b] });
		cout << res << '\n';
	}
}