#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;

	auto calc = [&](const auto& v) {
		vector cnt(32, 0);
		cnt[k - 1]++;
		for (int x : v) cnt[x]--;
		for (int i = 31; i; i--) cnt[i - 1] += cnt[i];
		for (int i = 31; i; i--) {
			int x = i, val = cnt[i]; cnt[i] = 0;
			for (int j = 2; j <= x; j++) {
				while (x % j == 0) x /= j, cnt[j] += val;
			}
		}
		auto res = 1LL;
		for (int i = 1; i < 32; i++) while (cnt[i]--) res *= i;
		return res;
	};

	vector c(n, 0LL), res(0, 0LL);
	auto dfs = [&](const auto& self, int dep, int s, int lim) -> void {
		if (dep == n) { if (!s) res.push_back(calc(c)); return; }
		for (int i = lim; i <= s; i++) {
			c[dep] = i;
			self(self, dep + 1, s - i, i);
		}
	};
	dfs(dfs, 0, k - 1, 0);

	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	for (auto x : res) cout << x << '\n';
}