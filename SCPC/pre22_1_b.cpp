#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return 1LL * a * b % mod;
}

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](int n, int k, auto v) {
	vector p(n + 1, 0LL);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + v[i];
	if (p[n] % k) return 0;
	if (p[n] == 0) {
		int cnt = count(p.begin() + 1, p.end(), 0);
		if (cnt < k - 1) return 0;
		int a = 1, b = 1;
		for (int i = 1; i < k; i++) {
			a = mul(a, cnt - i);
			b = mul(b, i);
		}
		return mul(a, pow(b, mod - 2));
	}
	i64 val = p[n] / k;
	vector dp(n + 1, 0);
	vector acc(k + 1, 0); acc[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (p[i] % val) continue;
		int j = p[i] / val;
		if (j < 1 || j > k) continue;
		dp[i] = acc[j - 1];
		acc[j] = add(acc[j], dp[i]);
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, k, v) << '\n';
	}
}