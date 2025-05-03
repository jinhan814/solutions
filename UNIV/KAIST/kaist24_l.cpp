#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, x, y; cin >> n >> x >> y;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto rec = [&](const auto& self, int cur, int prv) -> vector<int> {
		vector dp{ 0, 1 };
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			auto res = self(self, nxt, cur);
			int sz = dp.size() + res.size() - 1;
			if (sz > y + 1) sz = y + 1;
			vector ndp(sz, 0);
			for (int i = 1; i < dp.size(); i++) {
				for (int j = 0; j < res.size(); j++) {
					if (i + j >= sz) continue;
					int x = mul(dp[i], res[j]);
					ndp[i + j] = add(ndp[i + j], x);
				}
			}
			dp.swap(ndp);
		}
		for (int i : { x, y }) {
			if (i >= dp.size()) continue;
			dp[0] = add(dp[0], dp[i]);
		}
		return dp;
	};
	cout << rec(rec, 1, 0)[0] << '\n';
}