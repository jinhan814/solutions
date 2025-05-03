#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector cnt(n + 1, 0);
	vector dp1(n + 1, 0), dp2(n + 1, 0);
	for (int x : v) cnt[x]++;
	for (int i = 1; i <= n; i++) {
		for (int j = 2 * i; j <= n; j += i) {
			dp1[j] += cnt[i];
			dp2[i] += cnt[j];
		}
	}
	int res = n;
	for (int i = 1; i <= n; i++) {
		int a = cnt[i];
		int b = dp1[i] + dp2[i];
		res = min(res, 2 * n - 2 * a - b);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}