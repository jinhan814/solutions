#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector adj(n + 1, vector(0, pair(0, 0)));
	vector c(n + 1, 0), p(n + 1, 0);
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
	}
	while (k--) {
		int s; cin >> s;
		vector v(s, 0);
		for (int i = 0; i < s; i++) cin >> v[i];
		c[v[0]] = 1;
		for (int i = 1; i < s; i++) p[v[i - 1]] = v[i];
	}
	vector d(n + 1, array{ 1LL << 60, 1LL << 60 });
	set pq{ tuple(d[1][c[1]] = 0, 1, c[1]) };
	while (pq.size()) {
		auto [cdist, cur, s] = *pq.begin(); pq.erase(pq.begin());
		for (auto [nxt, cost] : adj[cur]) {
			int ns = 0;
			if (p[cur] == nxt && p[nxt] == 0 && s) continue;
			if (p[cur] == nxt && s) ns = 1;
			if (c[nxt]) ns = 1;
			if (d[nxt][ns] <= cdist + cost) continue;
			pq.erase({ d[nxt][ns], nxt, ns });
			pq.insert({ d[nxt][ns] = cdist + cost, nxt, ns });
		}
	}
	for (int i = 1; i <= n; i++) {
		if (d[i][0] > d[i][1]) swap(d[i][0], d[i][1]);
		if (d[i][0] >> 60) cout << -1 << ' ';
		else cout << d[i][0] << ' ';
	}
	cout << '\n';
}