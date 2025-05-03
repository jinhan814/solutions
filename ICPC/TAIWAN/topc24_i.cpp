#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n - 1, 0);
	for (int i = 0; i < n - 1; i++) cin >> v[i];

	vector dp(101, string(1 << n - 1, 2));
	auto rec = [&](const auto& self, int x, int s) -> bool {
		if (s + 1 >> n - 1) return 1;
		if (dp[x][s] != 2) return dp[x][s];
		for (int i = 0; i < n - 1; i++) {
			if (s >> i & 1) continue;
			if (v[i] % x || v[i] / x > 100) continue;
			if (self(self, v[i] / x, s | 1 << i)) return dp[x][s] = 1;
		}
		return dp[x][s] = 0;
	};

	vector res(0, 0);
	auto trace = [&](const auto& self, int x, int s) -> void {
		res.push_back(x);
		if (s + 1 >> n - 1) return;
		for (int i = 0; i < n - 1; i++) {
			if (s >> i & 1) continue;
			if (v[i] % x || v[i] / x > 100) continue;
			if (rec(rec, v[i] / x, s | 1 << i)) {
				self(self, v[i] / x, s | 1 << i);
				return;
			}
		}
	};

	int x = -1;
	for (int i = 1; i <= 100; i++) if (rec(rec, i, 0)) x = i;
	if (x != -1) {
		cout << "Yes" << '\n';
		trace(trace, x, 0);
		for (int x : res) cout << x << ' ';
		cout << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}