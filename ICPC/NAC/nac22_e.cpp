#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n) {
	vector s(n + 1, 1), p(0, 0);
	vector buc(n + 1, vector(0, 0));
	for (int i = 2; i <= n; i++) {
		if (s[i]) for (int j = i * i; j <= n; j += i) s[j] = 0;
		if (s[i]) p.push_back(i);
		for (int x : p) if (i % x == 0) buc[i].push_back(x);
	}
	return pair(p, buc);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	const int sz = max(100, 2 * n);
	const auto [p, buc] = calc(sz);

	vector dp(n + 1, vector(sz + 1, 0));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int i = 2; i <= sz; i++) {
			if (i == v[cur]) continue;
			dp[cur][i] = i;
		}
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			vector mn(sz + 1, 1 << 30);
			for (int i = 2; i <= sz; i++) {
				for (int x : buc[i]) mn[x] = min(mn[x], dp[nxt][i]);
			}
			for (int i = 2; i <= sz; i++) {
				int opt = 1 << 30;
				for (int x : buc[i]) opt = min(opt, mn[x]);
				dp[cur][i] += opt;
			}
		}
	};
	rec(rec, 1, 0);

	int res = 1 << 30;
	for (int i = 2; i <= sz; i++) res = min(res, dp[1][i]);
	cout << res << '\n';
}