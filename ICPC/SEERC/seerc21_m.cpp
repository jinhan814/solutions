#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, const int mod) {
	auto add = [&](int a, int b) {
		return a + b < mod ? a + b : a + b - mod;
	};
	auto mul = [&](int a, int b) {
		return 1LL * a * b % mod;
	};
	auto pow = [&](int x, int n) {
		int ret = 1;
		for (; n; n >>= 1) {
			if (n & 1) ret = mul(ret, x);
			x = mul(x, x);
		}
		return ret;
	};

	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int r) {
		return mul(fac[n], mul(inv[r], inv[n - r]));
	};

	vector res(n + 1, 0);
	auto rec = [&](const auto& self, i64 acc_m, i64 acc_s,
		int x, int cnt_x, int sz, int acc) -> void {
		i64 p = acc_m - acc_s;
		if (p + sz > n || x > n) return;
		if (cnt_x) res[p + sz] = add(res[p + sz], mul(acc, bino(p + sz, sz)));
		if (acc_m * x - (acc_s + x) > n) return;
		self(self, acc_m, acc_s, x + 1, 0, sz, acc);
		acc = mul(acc, mul(sz + 1, mul(inv[cnt_x + 1], fac[cnt_x])));
		self(self, acc_m * x, acc_s + x, x, cnt_x + 1, sz + 1, acc);
	};
	rec(rec, 1, 0, 2, 0, 0, 1);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, mod; cin >> n >> mod;
	auto res = sol(n, mod);
	for (int i = 2; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}