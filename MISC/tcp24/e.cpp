#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

auto [fac, inv] = [] {
	const int sz = 200'000;
	vector fac(sz + 1, 1);
	for (int i = 1; i <= sz; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(sz + 1, pow(fac[sz], mod - 2));
	for (int i = sz; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	return pair(fac, inv);
}();

auto bino = [](int n, int r) {
	return mul(fac[n], mul(inv[r], inv[n - r]));
};

auto sol = [](int n, int m, int k) {
	int res = 0;
	for (int i = 1; i <= n; i++) {
		int a = mul(k, mul(pow(k - 1, i - 1), pow(m, n - i)));
		int b = mul(bino(n - 1, i - 1), bino(m + i - 1, i));
		res = add(res, mul(a, b));
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m, k; cin >> n >> m >> k;
		cout << sol(n, m, k) << '\n';
	}
}