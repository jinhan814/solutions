#include <bits/stdc++.h>
using namespace std;

auto diameter = [](int n, const auto& adj) {
	int x = 1, mx = 0;
	for (int _ = 0; _ < 2; _++) {
		vector d(n + 1, -1), q(0, 0);
		d[x] = 0, q.push_back(x);
		while (q.size()) {
			auto x = q.back(); q.pop_back();
			for (int nxt : adj[x]) {
				if (d[nxt] != -1) continue;
				d[nxt] = d[x] + 1, q.push_back(nxt);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (d[x] >= d[i]) continue;
			x = i, mx = d[i];
		}
	}
	return mx;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		int d = diameter(n, adj);
		cout << (d % 3 != 2 ? "Go8" : "Neodoomer") << '\n';
	}
}