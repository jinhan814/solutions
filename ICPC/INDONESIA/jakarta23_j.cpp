#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];

	vector p(n, 1);
	for (int i = 1; i < n; i++) p[i] = 2 * p[i - 1] % mod;

	vector dp(n, 0), psum(n, 1);
	for (int i = 2; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (v[i] > v[i - 1]) dp[j] = mul(psum[j], p[i - 1 - j]);
			else dp[j] = j ? mul(psum[j - 1], p[i - 1 - j]) : 0;
		}
		for (int j = 0; j < n; j++) psum[j] = dp[j];
		for (int j = 1; j < n; j++) psum[j] = add(psum[j], psum[j - 1]);
	}
	cout << psum[n - 1] << '\n';
}