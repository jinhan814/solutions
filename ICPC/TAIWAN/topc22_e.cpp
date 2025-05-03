#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128;

i64 modadd(i64 a, i64 b, i64 mod) { return a + b < mod ? a + b : a + b - mod; }
i64 modmul(i64 a, i64 b, i64 mod) { return i128(a) * b % mod; }
i64 modpow(i64 x, i64 n, i64 mod) {
	i64 res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = modmul(res, x, mod);
		x = modmul(x, x, mod);
	}
	return res;
}

bool is_prime(i64 n) {
	if (n < 2 || n % 2 == 0 || n % 3 == 0) return n == 2 || n == 3;
	i64 k = __builtin_ctzll(n - 1), d = n - 1 >> k;
	for (i64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
		i64 p = modpow(a % n, d, n), i = k;
		while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
		if (p != n - 1 && i != k) return 0;
	}
	return 1;
}

i64 pollard(i64 n) {
	auto f = [n](i64 x) { return modadd(modmul(x, x, n), 3, n); };
	i64 x = 0, y = 0, t = 30, p = 2, i = 1, q;
	while (t++ % 40 || gcd(p, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if (q = modmul(p, abs(x - y), n)) p = q;
		x = f(x), y = f(f(y));
	}
	return gcd(p, n);
}

vector<i64> factor(i64 n) {
	if (n == 1) return {};
	if (is_prime(n)) return { n };
	i64 x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	sort(l.begin(), l.end());
	return l;
}

ostream& operator<<(ostream& out, i128 n) {
	string s;
	do s.push_back(n % 10 | 48); while (n /= 10);
	reverse(s.begin(), s.end());
	return out << s;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 k; cin >> k;
	auto fac = factor(k);
	auto dfs = [&](const auto& self, int i, i64 d) -> i64 {
		if (i == fac.size()) {
			if (k + d & 1) return -1;
			if (k + i128(k) * k / d & 1) return -1;
			return d;
		}
		int j = i;
		while (j < fac.size() && fac[i] == fac[j]) j++;
		i64 res = -1;
		for (int _ = 0; _ <= 2 * (j - i); _++, d *= fac[i]) {
			res = max(res, self(self, j, d));
			if (i128(d) * fac[i] >= k) break;
		}
		return res;
	};
	i128 d = dfs(dfs, 0, 1);
	i128 x = k + d >> 1;
	i128 y = k + i128(k) * k / d >> 1;
	cout << x << ' ' << y << '\n';
}