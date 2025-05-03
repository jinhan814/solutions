#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

auto fac = [] {
	vector fac(200'001, 1);
	for (int i = 1; i <= 200'000; i++) fac[i] = mul(fac[i - 1], i);
	return fac;
}();

auto inv = [] {
	vector inv(200'001, pow(fac[200'000], mod - 2));
	for (int i = 200'000; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	return inv;
}();

auto bino = [](int n, int r) {
	return mul(fac[n], mul(inv[r], inv[n - r]));
};

auto multinomial = [](auto v) -> int {
	int acc = 0;
	for (int x : v) acc += x;
	int ret = 1;
	for (int i = 0; i < v.size(); i++) {
		ret = mul(ret, bino(acc, v[i]));
		acc -= v[i];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s, t; cin >> s >> t;

	vector a(26, 0), b(26, 0);
	for (char c : s) a[c - 'A']++;
	for (char c : t) b[c - 'A']++;

	auto get_nxt = [](int a, int b, const auto& dp) {
		vector t(a + 1, 0);
		for (int i = 0; i <= a; i++) {
			int r1 = a - i < dp.size() ? dp[a - i] : 0;
			int r2 = bino(a, i);
			t[i] = mul(r1, r2);
		}
		for (int i = 1; i <= a; i++) t[i] = add(t[i], t[i - 1]);
		vector ndp(b + 1, 0);
		for (int i = 0; i <= b; i++) ndp[i] = t[min(a, b - i)];
		return ndp;
	};

	vector dp(1, 1);
	for (int i = 25; i >= 0; i--) dp = get_nxt(a[i], b[i], dp);
	cout << mul(dp[0], multinomial(a)) << '\n';
}