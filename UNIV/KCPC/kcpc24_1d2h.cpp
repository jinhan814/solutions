#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;
	sort(v.begin(), v.end());

	vector fac(n + m + 1, 1);
	for (int i = 1; i <= n + m; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + m + 1, pow(fac[n + m], mod - 2));
	for (int i = n + m; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int r) {
		if (r == 0 || r == n) return 1;
		return mul(fac[n], mul(inv[r], inv[n - r]));
	};

	if (k == 0) {
		cout << bino(n + m, n) << '\n';
		return 0;
	}

	vector dp1(k, 1), dp2(k, 0);
	for (int i = 0; i < k; i++) {
		auto [x, y] = v[i];
		dp2[i] = bino(x + y, x);
		for (int j = 0; j < i; j++) {
			auto [px, py] = v[j];
			if (!(px < x && py < y)) continue;
			if (dp1[i] < dp1[j] + 1) {
				dp1[i] = dp1[j] + 1;
				dp2[i] = 0;
			}
			if (dp1[i] == dp1[j] + 1) {
				int a = dp2[j];
				int b = bino(x - px + y - py - 2, x - px - 1);
				dp2[i] = add(dp2[i], mul(a, b));
			}
		}
	}

	int mx = ranges::max(dp1);
	int res = 0;
	for (int i = 0; i < k; i++) {
		if (dp1[i] != mx) continue;
		auto [x, y] = v[i];
		int a = dp2[i];
		int b = bino(n - x + m - y - 2, n - x - 1);
		res = add(res, mul(a, b));
	}
	cout << res << '\n';
}