#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	auto calc = [&](int s) {
		vector c(m, 0);
		for (int i = 0; i < n; i++) {
			if (~s >> i & 1) continue;
			for (int j = 0; j < m; j++) c[j] += v[i][j] == '.';
		}
		vector dp{ 0, 1 };
		for (int i = 0; i < m; i++) {
			vector ndp(2, 0);
			ndp[0] = dp[1];
			ndp[1] = mul(add(dp[0], dp[1]), (1 << c[i]) - 1);
			dp.swap(ndp);
		}
		return add(dp[0], dp[1]);
	};

	int res = 0;
	for (int s = 0; s < 1 << n; s++) {
		int pc = __builtin_popcount(s);
		int val = calc(s);
		if (n - pc & 1) res = sub(res, val);
		else res = add(res, val);
	}
	cout << res << '\n';
}