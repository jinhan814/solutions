#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	string b = "cdhs";
	int res = 1 << 30;
	for (int i = 0; i < 24; i++) {
		vector dp(4, 0);
		for (char c : s) {
			int x = b.find(c);
			vector ndp = dp;
			for (int i = 0; i <= x; i++) ndp[x] = max(ndp[x], dp[i] + 1);
			dp.swap(ndp);
		}
		res = min(res, (int)s.size() - ranges::max(dp));
		next_permutation(b.begin(), b.end());
	}
	cout << res << '\n';
}