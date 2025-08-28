#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto e) {
	vector fac(n + 1, 1LL);
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
	vector g(n, 0);
	for (auto [a, b] : e) {
		g[a - 1] |= 1 << b - 1;
		g[b - 1] |= 1 << a - 1;
	}
	vector dp(1 << n, -1LL);
	auto rec = [&](const auto& self, int s) -> i64 {
		int cn = __builtin_popcount(s);
		int ck = k;
		for (int i = n; i > cn; i--) if (ck > i) ck -= 2;
		if (ck <= 1) return 0;
		if (ck >= 2 * cn - 1) return fac[cn];
		i64& ret = dp[s];
		if (ret != -1) return ret;
		ret = 0;
		for (int i = 0; i < n; i++) {
			if (~s >> i & 1) continue;
			if (ck <= cn && g[i] & s) continue;
			ret += self(self, s ^ 1 << i);
		}
		return ret;
	};
	return rec(rec, (1 << n) - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		int m; cin >> m;
		vector e(m, array{ 0, 0 });
		for (auto& [a, b] : e) cin >> a >> b;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, k, e) << '\n';
	}
}