#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, q, r; cin >> n >> q >> r;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
		vector in(n + 1, 0), r_in(n + 1, 0), top(n + 1, 0);
		{
			int ord = 0;
			auto dfs1 = [&](const auto& f, int cur, int prv) -> void {
				auto it = find(adj[cur].begin(), adj[cur].end(), prv);
				if (it != adj[cur].end()) adj[cur].erase(it);
				for (int& nxt : adj[cur]) if (nxt != prv) {
					dep[nxt] = dep[cur] + 1;
					par[nxt] = cur;
					f(f, nxt, cur);
					sz[cur] += sz[nxt];
					if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
				}
			};
			auto dfs2 = [&](const auto& f, int cur) -> void {
				in[cur] = ++ord;
				r_in[ord] = cur;
				for (int nxt : adj[cur]) {
					top[nxt] = nxt == adj[cur][0] ? top[cur] : nxt;
					f(f, nxt);
				}
			};
			dfs1(dfs1, 1, 0);
			dfs2(dfs2, top[1] = 1);
		}

		auto lca = [&](int a, int b) {
			while (top[a] != top[b]) {
				if (dep[top[a]] < dep[top[b]]) swap(a, b);
				a = par[top[a]];
			}
			if (dep[a] > dep[b]) swap(a, b);
			return a;
		};

		auto lift = [&](int x, int k) {
			while (dep[x] - dep[par[top[x]]] <= k) {
				k -= dep[x] - dep[par[top[x]]];
				x = par[top[x]];
			}
			return r_in[in[x] - k];
		};

		auto query = [&](int x) {
			if (r == x) return n;
			if (lca(r, x) == x) return n - sz[lift(r, dep[r] - dep[x] - 1)];
			else return sz[x];
		};

		cout << "Case #" << tc_num << ':' << '\n';
		while (q--) {
			int t, x; cin >> t >> x;
			if (t == 0) r = x;
			else cout << query(x) << '\n';
		}
	}
}