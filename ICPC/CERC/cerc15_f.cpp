#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e6 + 3;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

auto conv = [](auto a, auto b) {
	auto conv_naive = [](const auto& a, const auto& b) {
		vector c(a.size() + b.size(), 0);
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++)
				c[i + j] = add(c[i + j], mul(a[i], b[j]));
		}
		return c;
	};
	auto rec = [&](const auto& self, const auto& a, const auto& b) -> vector<int> {
		if (a.size() <= 64) return conv_naive(a, b);
		const int m = a.size() >> 1;
		vector a0(a.begin(), a.begin() + m), a1(a.begin() + m, a.end());
		vector b0(b.begin(), b.begin() + m), b1(b.begin() + m, b.end());
		vector z0 = self(self, a0, b0), z2 = self(self, a1, b1);
		for (int i = 0; i < m; i++) a0[i] = add(a0[i], a1[i]);
		for (int i = 0; i < m; i++) b0[i] = add(b0[i], b1[i]);
		vector z1 = self(self, a0, b0);
		for (int i = 0; i < 2 * m; i++) z1[i] = sub(z1[i], add(z0[i], z2[i]));
		vector res(a.size() + b.size(), 0);
		for (int i = 0; i < z0.size(); i++) res[i] = add(res[i], z0[i]);
		for (int i = 0; i < z1.size(); i++) res[i + m] = add(res[i + m], z1[i]);
		for (int i = 0; i < z2.size(); i++) res[i + 2 * m] = add(res[i + 2 * m], z2[i]);
		return res;
	};
	const int n = a.size(), m = b.size();
	const int sz = 1 << __lg(max(n, m) - 1) + 1;
	a.resize(sz); b.resize(sz);
	vector c = rec(rec, a, b);
	c.resize(n + m - 1);
	return c;
};

const auto [fac, inv] = [] {
	const int sz = 400'000;
	vector fac(sz + 1, 1);
	for (int i = 1; i <= sz; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(sz + 1, pow(fac[sz], mod - 2));
	for (int i = sz; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	return pair(fac, inv);
}();

auto bino = [](int n, int r) {
	return mul(fac[n], mul(inv[r], inv[n - r]));
};

auto f = [](int n, int a, int b) {
	vector p(n + 1, 0), q(n + 1, 0);
	for (int i = 0; i <= n; i++) {
		p[i] = mul(pow(a, i), inv[i]);
		q[i] = mul(pow(b, i), inv[i]);
	}
	vector c = conv(p, q);
	int ret = 0;
	for (int i = 0; i <= 2 * n; i++) {
		ret = add(ret, mul(fac[i], c[i]));
	}
	return ret;
};

auto sol = [](int n, int a, int b, int c, auto v) {
	int ret = mul(c, f(n - 2, a, b));
	for (int i = 2; i <= n; i++) {
		int res = v[0][i];
		res = mul(res, pow(a, n - 1));
		res = mul(res, pow(b, n - i));
		res = mul(res, bino(2 * n - 2 - i, n - 2));
		ret = add(ret, res);
	}
	for (int i = 2; i <= n; i++) {
		int res = v[1][i];
		res = mul(res, pow(a, n - i));
		res = mul(res, pow(b, n - 1));
		res = mul(res, bino(2 * n - 2 - i, n - 2));
		ret = add(ret, res);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b, c; cin >> n >> a >> b >> c;
	vector v(2, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) cin >> v[0][i];
	for (int i = 1; i <= n; i++) cin >> v[1][i];
	cout << sol(n, a, b, c, v) << '\n';
}