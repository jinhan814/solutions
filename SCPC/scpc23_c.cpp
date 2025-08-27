#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	i64 query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<i64> tree;
};

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return 0;
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

struct info {
	i64 a, b, i;
	auto operator<=> (const info& x) const {
		return a * x.b <=> x.a * b;
	}
};

auto sol = [](int n, int q, auto par, auto v, auto qs) {
	vector adj(n + 1, vector(0, 0));
	vector a(n + 1, 0LL);
	vector b(n + 1, 0);
	priority_queue<info, vector<info>, greater<>> pq;
	for (int i = 2; i <= n; i++) {
		adj[par[i]].push_back(i);
		a[i] = v[i];
		b[i] = 1;
		pq.push({ a[i], b[i], i });
	}
	vector c(n + 1, 0);
	union_find uf(n + 1);
	for (int k = 1; pq.size(); k++) {
		int i = pq.top().i; pq.pop();
		int j = uf.find(par[i]);
		if (c[i]) continue;
		c[i] = k;
		a[j] += a[i];
		b[j] += b[i];
		uf.merge(j, i);
		if (j != 1) pq.push({ a[j], b[j], j });
	}
	vector pri(n + 1, 0);
	priority_queue<pii, vector<pii>, greater<>> s;
	s.push(pair(c[1], 1));
	for (int k = 1; s.size(); k++) {
		int i = s.top().second; s.pop();
		pri[i] = k;
		for (int j : adj[i]) s.push(pair(c[j], j));
	}
	vector sz(n + 1, 1);
	for (int i = n; i > 1; i--) sz[par[i]] += sz[i];
	for (int i = 1; i <= n; i++) {
		for (int& j : adj[i]) {
			if (sz[adj[i][0]] >= sz[j]) continue;
			swap(adj[i][0], j);
		}
	}
	vector dp(n + 1, 0LL);
	fenwick t1(n), t2(n);
	auto rec = [&](const auto& self, int cur) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == adj[cur][0]) continue;
			self(self, nxt);
			auto f = [&](const auto& self, int i) -> void {
				t1.update(pri[i], -v[i]);
				t2.update(pri[i], -1);
				for (int j : adj[i]) self(self, j);
			};
			f(f, nxt);
		}
		if (adj[cur].size()) {
			self(self, adj[cur][0]);
			dp[cur] = dp[adj[cur][0]];
		}
		auto g = [&](const auto& self, int i) -> void {
			i64 s = t1.query(1, pri[i]);
			i64 t = t2.query(pri[i], n);
			dp[cur] += s + v[i] * t + v[i];
			t1.update(pri[i], v[i]);
			t2.update(pri[i], 1);
			for (int j : adj[i]) {
				if (j == adj[cur][0]) continue;
				self(self, j);
			}
		};
		g(g, cur);
	};
	rec(rec, 1);
	vector res(q, 0LL);
	for (int i = 0; i < q; i++) res[i] = dp[qs[i]];
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector par(n + 1, 0), v(n + 1, 0);
		for (int i = 2; i <= n; i++) cin >> par[i];
		for (int i = 1; i <= n; i++) cin >> v[i];
		int q; cin >> q;
		vector qs(q, 0);
		for (int i = 0; i < q; i++) cin >> qs[i];
		auto res = sol(n, q, par, v, qs);
		cout << "Case #" << tc_num << '\n';
		for (int i = 0; i < q; i++) cout << res[i] << ' ';
		cout << '\n';
	}
}