#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector adj(1 << n | 1, vector(0, 0));
	vector par(1 << n | 1, 0);
	for (auto [a, b] : v) {
		adj[a].push_back(b);
		par[b] = a;
	}
	int x = -1, y = -1;
	for (int i = 1; i <= 1 << n; i++) {
		if (par[i]) continue;
		if (x == -1) x = i;
		else y = i;
	}
	if (adj[x].size() == adj[y].size()) {
		if (x > y) swap(x, y);
		return vector{ pair(x, y), pair(y, x) };
	}
	if (adj[x].size() < adj[y].size()) {
		swap(x, y);
	}
	vector dp(1 << n | 1, -1);
	auto calc = [&](const auto& self, int cur) -> int {
		int& ret = dp[cur];
		if (ret != -1) return ret;
		if (adj[cur].empty()) return ret = 0;
		vector v(0, 0);
		for (int nxt : adj[cur]) {
			v.push_back(self(self, nxt));
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) {
			if (v[i] != i) return ret = -1;
		}
		return ret = v.size();
	};
	vector res(0, pair(0, 0));
	auto rec = [&](const auto& self, int cur, int dep) -> void {
		if (adj[cur].size() != dep) {
			res.push_back({ cur, y });
			return;
		}
		vector buc(dep + 1, vector(0, 0));
		for (int nxt : adj[cur]) {
			int val = calc(calc, nxt);
			buc[val + 1].push_back(nxt);
		}
		int ndep = -1;
		for (int i = 1; i <= dep; i++) {
			if (buc[i].size() == 1) continue;
			ndep = i - 1;
		}
		for (int nxt : buc[0]) self(self, nxt, ndep);
		for (int i = 1; i <= dep; i++) {
			if (buc[i].size() != 2) continue;
			for (int nxt : buc[i]) self(self, nxt, ndep);
		}
	};
	rec(rec, x, n);
	sort(res.begin(), res.end());
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v((1 << n) - 2, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;
	auto res = sol(n, v);
	for (auto [a, b] : res) cout << a << ' ' << b << '\n';
}