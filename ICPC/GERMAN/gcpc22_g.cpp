#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](const auto& adj) {
	const int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto dfs = [&](const auto& self, int cur) -> int {
		int ret = dfn[cur] = ++dfs_cnt;
		s.push_back(cur);
		for (int nxt : adj[cur]) {
			if (!dfn[nxt]) ret = min(ret, self(self, nxt));
			else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
		}
		if (ret == dfn[cur]) {
			scc_cnt++;
			while (s.size()) {
				int x = s.back(); s.pop_back();
				scc[x] = scc_cnt;
				if (x == cur) break;
			}
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
	return pair(scc_cnt, scc);
};

struct two_sat {
	two_sat(int n) : n(n), adj(n + 1 << 1), scc(n + 1 << 1) {}
	void add_clause(int a, int na, int b, int nb) {
		a = a << 1 | na;
		b = b << 1 | nb;
		adj[a ^ 1].push_back(b);
		adj[b ^ 1].push_back(a);
	}
	bool satisfiable() {
		tie(scc_cnt, scc) = get_scc(adj);
		for (int i = 1; i <= n; i++) if (scc[i << 1] == scc[i << 1 | 1]) return 0;
		return 1;
	}
private:
	int n, scc_cnt;
	vector<vector<int>> adj;
	vector<int> scc;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(8, 0);
	for (int i = 1; i <= 7; i++) cin >> v[i], v[i] += v[i - 1];

	two_sat sat(v[7]);
	while (n--) {
		vector t(7, 0);
		for (int i = 0; i < 7; i++) cin >> t[i];
		for (int i = 0; i < 7; i++) for (int j = i + 1; j < 7; j++) {
			int a = v[i] + abs(t[i]);
			int b = v[j] + abs(t[j]);
			sat.add_clause(a, t[i] > 0, b, t[j] > 0);
		}
	}
	int t1, t2; cin >> t1 >> t2;
	int a = v[5] + abs(t1);
	int b = v[6] + abs(t2);
	sat.add_clause(a, t1 < 0, a, t1 < 0);
	sat.add_clause(b, t2 < 0, b, t2 < 0);

	bool res = sat.satisfiable();
	cout << (res ? "possible" : "impossible") << '\n';
}