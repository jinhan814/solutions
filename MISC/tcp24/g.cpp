#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

auto calc = [](int sz) {
	vector c(sz + 1, 0), dp(sz + 1, 0);
	for (int i = 2; i <= sz; i++) {
		if (c[i]) continue;
		for (int j = 2 * i; j <= sz; j += i) c[j] = 1;
		for (int j = i - 1; j + 1 <= sz; j += i - 1) dp[j + 1]++;
	}
	return dp;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	vector dp = calc(1'000'000);
	while (tc--) {
		int n; cin >> n;
		cout << pow(2, dp[n]) << '\n';
	}
}