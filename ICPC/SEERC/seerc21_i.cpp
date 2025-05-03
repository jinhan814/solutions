#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		p[a] += p[b];
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

struct max_flow {
	max_flow(int n) : sz(n), par(n), adj(n) {}
	void add_edge(int a, int b, int cap, bool is_directed = 1) {
		edge e{ b, adj[b].size(), cap };
		edge r{ a, adj[a].size(), is_directed ? 0 : cap };
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

auto sol = [](int n, int m, auto a, auto b) {
	union_find uf(n * m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i && a[i - 1][j] == a[i][j]) {
				uf.merge(i * m + j - m, i * m + j);
			}
			if (j && a[i][j - 1] == a[i][j]) {
				uf.merge(i * m + j - 1, i * m + j);
			}
		}
	}

	vector conv(n * m, 0);
	vector type(n * m, 0);
	int sz = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i * m + j != uf.find(i * m + j)) continue;
			conv[i * m + j] = sz;
			type[sz] = a[i][j] & 1;
			sz++;
		}
	}

	vector adj(sz, vector(0, 0));
	vector dp(sz, array{ 0, 0 });
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i && a[i - 1][j] != a[i][j]) {
				int s = conv[uf.find(i * m + j)];
				int t = conv[uf.find(i * m + j - m)];
				adj[s].push_back(t);
				adj[t].push_back(s);
			}
			if (j && a[i][j - 1] != a[i][j]) {
				int s = conv[uf.find(i * m + j)];
				int t = conv[uf.find(i * m + j - 1)];
				adj[s].push_back(t);
				adj[t].push_back(s);
			}
			int f = a[i][j] == b[i][j];
			dp[conv[uf.find(i * m + j)]][f]++;
		}
	}
	for (int i = 0; i < sz; i++) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
	}

	int res = 0;
	max_flow flow(sz + 2);
	for (int i = 0; i < sz; i++) {
		res += dp[i][0];
		if (dp[i][0] - dp[i][1] <= 0) continue;
		res += dp[i][1] - dp[i][0];
		if (!type[i]) {
			flow.add_edge(sz, i, dp[i][0] - dp[i][1]);
			for (int j : adj[i]) flow.add_edge(i, j, 1 << 30);
		}
		else {
			flow.add_edge(i, sz + 1, dp[i][0] - dp[i][1]);
		}
	}
	res += flow.flow(sz, sz + 1);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, string{});
	vector b(n, string{});
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}