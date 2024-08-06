#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	auto get_dist = [&](int x) {
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

	auto get_opt = [&](const auto& cmp) {
		int res = 0;
		for (int i = 1; i <= n; i++) if (cmp(res) < cmp(i)) res = i;
		return res;
	};

	int x = get_opt([d1 = get_dist(1)](int i) { return d1[i]; });
	auto dx = get_dist(x);

	int y = get_opt([&](int i) { return dx[i]; });
	auto dy = get_dist(y);

	int z = get_opt([&](int i) { return dx[i] + dy[i]; });
	auto dz = get_dist(z);

	auto query = [&](int a, int b) -> int {
		int rx = dx[a] + dx[b];
		int ry = dy[a] + dy[b];
		int rz = dz[a] + dz[b];
		return max({ rx, ry, rz });
	};

	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		cout << query(a, b) << '\n';
	}
}