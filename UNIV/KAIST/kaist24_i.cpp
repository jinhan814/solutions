#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }
int inv(int x) { return pow(x, mod - 2); }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(2, vector(n, array{ 0, 0, 0 }));
	for (auto& [r, s, p] : v[0]) cin >> r >> s >> p;
	for (auto& [r, s, p] : v[1]) cin >> r >> s >> p;
	int res = 0;
	vector dp{ 1, 0, 0 };
	for (int i = 0; i < n; i++) {
		auto [r1, s1, p1] = v[0][i];
		auto [r2, s2, p2] = v[1][i];
		int t = mul(inv(r1 + s1 + p1), inv(r2 + s2 + p2));
		int a = mul(add(mul(r1, s2), add(mul(s1, p2), mul(p1, r2))), t);
		int b = mul(add(mul(r2, s1), add(mul(s2, p1), mul(p2, r1))), t);
		int c = sub(1, add(a, b));
		res = add(res, mul(dp[1], c));
		vector ndp(3, 0);
		ndp[0] = mul(dp[0], c);
		ndp[1] = mul(add(dp[0], add(dp[1], dp[2])), a);
		ndp[2] = mul(add(dp[0], add(dp[1], dp[2])), b);
		dp.swap(ndp);
	}
	cout << res << '\n';
}