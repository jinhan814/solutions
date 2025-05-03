#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;

	auto f = [](char c) {
		return string("AEIOUY").find(c) != -1;
	};

	auto update = [&](auto& dp, const string& s) {
		vector ndp(3, 1 << 20);
		int p = 0;
		while (p < s.size() && f(s[p]) == f(s[0])) p++;
		if (f(s[0])) {
			ndp[0] = min(ndp[0], dp[0] + 1);
			ndp[0] = min(ndp[0], dp[1] + 1);
			ndp[0] = min(ndp[0], dp[2] + 1);
			if (p < s.size()) ndp[1] = min(ndp[1], dp[0] + p + 1);
			if (p < s.size()) ndp[2] = min(ndp[2], dp[1] + p + 1);
		}
		else {
			if (p < s.size() && p == 1) ndp[0] = min(ndp[0], dp[1] + p + 1);
			if (p < s.size() && p <= 2) ndp[0] = min(ndp[0], dp[0] + p + 1);
			ndp[1] = min(ndp[1], dp[0] + 1);
			ndp[2] = min(ndp[2], dp[1] + 1);
		}
		dp.swap(ndp);
	};

	vector dp{ 0, 1 << 20, 1 << 20 };
	for (int i = 0; i < n; i++) { string s; cin >> s; update(dp, s); }
	int res = ranges::min(dp);
	if (res >> 20) cout << '*' << '\n';
	else cout << res << '\n';
}