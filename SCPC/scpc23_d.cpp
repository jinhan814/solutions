#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
constexpr int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
constexpr int mul(int a, int b) { return 1LL * a * b % mod; }
constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](int n, int k) {
	if (k < n - 1 || 2 * n - 3 < k) return 0;
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	vector dp(n + 1, vector(n, 0)); dp[0][0] = 1;
	vector p(n, 0); p[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i - 1; j++) {
			dp[i][j] = mul(p[j], fac[i - 1]);
		}
		for (int j = n - 1; j >= 0; j--) {
			p[j] = mul(dp[i][j], inv[i]);
			if (j) p[j] = add(p[j], p[j - 1]);
		}
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int acc = 0;
		int x = mul(fac[n - 1], mul(inv[i - 1], inv[n - i]));
		for (int j = 0; j <= k - n + 1; j++) {
			int a = dp[i - 1][j];
			int b = dp[n - i][k - n + 1 - j];
			acc = add(acc, mul(a, b));
		}
		ret = add(ret, mul(acc, x));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, k) << '\n';
	}
}