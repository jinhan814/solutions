#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int mod = 119 << 23 | 1;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }
int inv(int x) { return pow(x, mod - 2); }

int main() {
	fastio;
	int n; cin >> n;
	vector a(n, array{ 0, 0, 0 });
	vector b(n, array{ 0, 0, 0 });
	for (auto& [r, s, p] : a) cin >> r >> s >> p;
	for (auto& [r, s, p] : b) cin >> r >> s >> p;
	vector c(n, vector(3, 0));
	for (int i = 0; i < n; i++) {
		auto [r1, s1, p1] = a[i];
		auto [r2, s2, p2] = b[i];
		int x = add(mul(r1, s2), add(mul(s1, p2), mul(p1, r2)));
		int y = add(mul(r2, s1), add(mul(s2, p1), mul(p2, r1)));
		int t = mul(inv(r1 + s1 + p1), inv(r2 + s2 + p2));
		x = mul(x, t), y = mul(y, t);
		c[i] = { sub(1, add(x, y)), x, y };
	}
	vector dp = c[0];
	int res = 0;
	for (int i = 1; i < n; i++) {
		res = add(res, mul(dp[1], c[i][0]));
		vector ndp(3, 0);
		ndp[0] = mul(dp[0], c[i][0]);
		ndp[1] = mul(add(dp[0], add(dp[1], dp[2])), c[i][1]);
		ndp[2] = mul(add(dp[0], add(dp[1], dp[2])), c[i][2]);
		dp.swap(ndp);
	}
	cout << res << '\n';
}