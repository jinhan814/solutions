#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int x, int l, int r, int a, int b, int p) -> int {
	// mod p
	auto add = [&](int a, int b) { return a + b < p ? a + b : a + b - p; };
	auto sub = [&](int a, int b) { return a < b ? a - b + p : a - b; };
	auto mul = [&](int a, int b) { return 1LL * a * b % p; };
	auto pow = [&](int x, int n) {
		int ret = 1;
		for (; n; n >>= 1, x = mul(x, x)) if (n & 1) ret = mul(ret, x);
		return ret;
	};
	auto inv = [&](int x) { return pow(x, p - 2); };

	// baby step giant step
	const int s = 2'000;
	const int m = (n - 1) / s;
	unordered_set buc{ -1 };
	for (int i = 0; i < m; i++) buc.insert(inv(pow(a, i * s)));
	auto check = [&](int rhs) -> bool { // rhs \in { a^0, ..., a^{n-1} }
		for (int i = m * s; i < n; i++) {
			int val = pow(a, i);
			if (val == rhs) return 1;
		}
		int x = inv(rhs);
		for (int i = 0; i < s; i++) {
			if (buc.count(x)) return 1;
			x = mul(x, a);
		}
		return 0;
	};

	// edge case
	if (a == 1) {
		int res = 0;
		for (int i = l; i <= r; i++) {
			int val = mul(sub(x, i), inv(b));
			if (val < n) res++;
		}
		return res;
	}

	// general case
	int res = 0;
	int t = mul(b, inv(a - 1));
	for (int i = l; i <= r; i++) {
		if (add(i, t) == 0) {
			if (add(x, t) == 0) res++;
		}
		else {
			int rhs = mul(inv(add(i, t)), add(x, t));
			if (check(rhs)) res++;
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, x, l, r, a, b, p; cin >> n >> x >> l >> r >> a >> b >> p;
		int r1 = sol(n, x, l, r, a, b, p);
		int r2 = r - l + 1;
		int g = gcd(r1, r2);
		cout << r1 / g << '/' << r2 / g << '\n';
	}
}