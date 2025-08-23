#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto adj) {
	if (n == 3) return 1LL;
	vector cand(0, 0);
	for (int i = 1; i <= n; i++) {
		if (adj[i].size() != 3) continue;
		cand.push_back(i);
	}
	auto rec = [&](const auto& self, int cur, int prv) -> int {
		if (cur == cand[1]) return 0;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			if (cur == cand[0] && nxt == cand[1]) continue;
			return self(self, nxt, cur) + 1;
		}
	};
	i64 x = rec(rec, cand[0], -1);
	return x * (x - 1) / 2 + (n - x) * (n - x - 1) / 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector adj(n + 1, vector(0, 0));
		for (int i = 0; i < n + 1; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, adj) << '\n';
	}
}