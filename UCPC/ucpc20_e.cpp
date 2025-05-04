#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2e9 + 7;

struct dinic {
	dinic(int n) : dep(n), idx(n), adj(n) {}
	void add_edge(int a, int b, int cap, int rcap = 0) {
		edge e{ b, (int)adj[b].size(), cap };
		edge r{ a, (int)adj[a].size(), rcap };
		adj[a].push_back(e);
		adj[b].push_back(r);
	}
	bool bfs(int s, int t) {
		fill(dep.begin(), dep.end(), 0);
		deque q{ s }; dep[s] = 1;
		while (q.size()) {
			int cur = q.front(); q.pop_front();
			for (const auto& [nxt, _, res] : adj[cur]) {
				if (res == 0 || dep[nxt]) continue;
				q.push_back(nxt);
				dep[nxt] = dep[cur] + 1;
			}
		}
		return dep[t] != 0;
	}
	int dfs(int cur, int t, int acc) {
		if (cur == t || acc == 0) return acc;
		for (int& i = idx[cur]; i < adj[cur].size(); i++) {
			auto& [nxt, inv, res] = adj[cur][i];
			if (res == 0 || dep[nxt] != dep[cur] + 1) continue;
			int val = dfs(nxt, t, min(acc, res));
			if (val == 0) continue;
			res -= val;
			adj[nxt][inv].res += val;
			return val;
		}
		return 0;
	}
	int flow(int s, int t) {
		int res = 0;
		while (bfs(s, t)) {
			fill(idx.begin(), idx.end(), 0);
			while (1) {
				int f = dfs(s, t, inf);
				if (f == 0) break;
				res += f;
			}
		}
		return res;
	}
	vector<int> mincut(int s, int t) {
		flow(s, t);
		vector res(adj.size(), 0);
		for (int i = 0; i < adj.size(); i++) res[i] = dep[i] > 0;
		return res;
	}
private:
	struct edge { int nxt, inv, res; };
	vector<int> dep, idx;
	vector<vector<edge>> adj;
};

auto bfs = [](int n, int s, int t, auto adj) {
	vector d(n + 1, -1); d[s] = 1;
	deque q{ s };
	while (q.size()) {
		int x = q.front(); q.pop_front();
		for (int nx : adj[x]) {
			if (d[nx] != -1) continue;
			d[nx] = d[x] + 1;
			q.push_back(nx);
		}
	}
	return d[t];
};

auto sol = [](int n, int k, int s, int t, auto v, auto adj) {
	dinic g(2 * k * n);
	for (int dep = 0; dep < k; dep++) {
		for (int i = 1; i <= n; i++) {
			int pi = 2 * n * dep + 2 * i - 2;
			g.add_edge(pi, pi + 1, v[i]);
			if (dep + 1 < k) g.add_edge(pi, 2 * n + pi + 1, inf);
			for (int j : adj[i]) {
				int pj = 2 * n * dep + 2 * j - 2;
				g.add_edge(pi + 1, pj, inf);
			}
		}
	}
	auto c = g.mincut(2 * s - 2, 2 * n * (k - 1) + 2 * t - 1);
	vector res(0, 0);
	for (int i = 1; i <= n; i++) {
		for (int dep = 0; dep < k; dep++) {
			int pi = 2 * n * dep + 2 * i - 2;
			if (c[pi] && !c[pi + 1]) {
				res.push_back(i);
				break;
			}
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	int s, t; cin >> s >> t;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	int d = bfs(n, s, t, adj);
	if (d == -1) return cout << 0 << '\n', 0;
	if (d < k) return cout << -1 << '\n', 0;
	auto res = sol(n, k, s, t, v, adj);
	cout << res.size() << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}