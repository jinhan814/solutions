#include <bits/stdc++.h>
using namespace std;

constexpr int sz = 2501;

auto sol = [](int n, auto v) {
	int m = 0;
	for (int i = 0; i < n; i++) m += v[i];
	bitset<sz * sz> dp; dp[0] = 1;
	for (int x : v) dp |= dp << x | dp << sz * x;
	int res = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= m; j++) {
			int idx = i * sz + j;
			if (!dp[idx]) continue;
			res = max(res, min({ i, j, m - i - j }));
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n; cin >> n;
		if (!n) break;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}