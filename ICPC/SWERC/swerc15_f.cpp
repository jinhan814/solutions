#include <bits/stdc++.h>
using namespace std;

struct max_flow {
	max_flow(int n) : sz(n), par(n), adj(n) {}
	void add_edge(int a, int b, int cap, int rcap = 0) {
		edge e{ b, adj[b].size(), cap };
		edge r{ a, adj[a].size(), rcap };
		adj[a].push_back(e);
		adj[b].push_back(r);
	}
	int bfs(int s, int t) {
		fill(par.begin(), par.end(), -1);
		deque q{ pair(s, 1 << 30) }; par[s] = 1 << 30;
		while (q.size()) {
			auto [cur, f] = q.front(); q.pop_front();
			for (auto e : adj[cur]) {
				if (par[e.nxt] != -1 || e.res == 0) continue;
				par[e.nxt] = e.inv;
				if (e.nxt == t) return min(f, e.res);
				q.push_back({ e.nxt, min(f, e.res) });
			}
		}
		return 0;
	}
	int flow(int s, int t) {
		int res = 0;
		while (1) {
			int f = bfs(s, t);
			if (!f) break;
			res += f;
			for (int cur = t; cur != s;) {
				auto [prv, i, _] = adj[cur][par[cur]];
				adj[cur][par[cur]].res += f;
				adj[prv][i].res -= f;
				cur = prv;
			}
		}
		return res;
	}
private:
	struct edge { int nxt, inv, res; };
	int sz;
	vector<int> par;
	vector<vector<edge>> adj;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b; cin >> n >> m >> a >> b;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	int s = n * m, t = n * m + 1;
	max_flow flow(n * m + 2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] == '.') flow.add_edge(s, i * m + j, b);
			else flow.add_edge(i * m + j, t, b);
			if (i) flow.add_edge((i - 1) * m + j, i * m + j, a, a);
			if (j) flow.add_edge(i * m + j - 1, i * m + j, a, a);
		}
	}
	cout << flow.flow(s, t) << '\n';
}