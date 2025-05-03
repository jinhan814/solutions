#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int fac[1'000'001], inv[1'000'001];

int mul(int a, int b) {
	return 1LL * a * b % mod;
}

int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

int bino(int n, int r) {
	if (r == 0 || r == n) return 1;
	return mul(fac[n], mul(inv[r], inv[n - r]));
}

int sol(int n, int a, int b) {
	if (a > b) swap(a, b);
	if (n <= 3) return 1;
	if (a == 1 && b == n) return 1;
	if (b == n) b -= a - 1, a = 1;
	int res = 0;
	for (int i = a; i < b; i++) {
		int x = bino(i - 1, a - 1);
		int y = bino(n - i - 2, n - b - 1);
		res += mul(x, y);
		if (res >= mod) res -= mod;
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	fac[0] = 1;
	for (int i = 1; i <= 1'000'000; i++) fac[i] = mul(fac[i - 1], i);
	inv[1'000'000] = pow(fac[1'000'000], mod - 2);
	for (int i = 1'000'000; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	int N; cin >> N;
	while (N--) {
		int n, a, b; cin >> n >> a >> b;
		cout << sol(n, a, b) << '\n';
	}
}