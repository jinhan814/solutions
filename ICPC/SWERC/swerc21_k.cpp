#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	vector p(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		cin >> p[i];
		adj[p[i]].push_back(i);
	}

	vector sz(n + 1, 1);
	vector dp(n + 1, 0LL);
	for (int i = n; i >= 2; i--) sz[p[i]] += sz[i];
	for (int i = 1; i <= n; i++) dp[i] = sz[i];
	for (int i = n; i >= 2; i--) dp[p[i]] += dp[i];
	for (int i = 2; i <= n; i++) dp[i] = dp[p[i]] - sz[i] + (n - sz[i]);

	auto subset_sum = [](const auto& v, const int s) -> int {
		if (v.back() >= s / 2) return v.back();
		bitset<1 << 20> b; b[0] = 1;
		for (int i = 0, j = 0; i < v.size(); i = j) {
			while (j < v.size() && v[i] == v[j]) j++;
			int cnt = j - i;
			for (int bit = 0; cnt - 1 >> bit; cnt -= 1 << bit++) b |= b << (v[i] << bit);
			b |= b << (v[i] * cnt);
		}
		int opt = 0;
		for (int i = 1; i < s; i++) {
			if (!b[i]) continue;
			if (abs(2 * opt - s) > abs(2 * i - s)) opt = i;
		}
		return opt;
	};

	auto calc = [&](int i) {
		auto res = dp[i] - n;
		vector buc(0, 0);
		if (i > 1) buc.push_back(n - sz[i]);
		for (int j : adj[i]) buc.push_back(sz[j]);
		sort(buc.begin(), buc.end());
		auto opt = subset_sum(buc, n - 1);
		res += (opt + 1LL) * (n - opt);
		return res;
	};

	auto opt = 0LL;
	for (int i = 1; i <= n; i++) opt = max(opt, calc(i));
	cout << opt << '\n';
}